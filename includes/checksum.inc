<?php

/**
 * @file
 * Functionality for working with checksums in Fedora.
 */

/**
 * Instantiates Tuque without the Drupal wrapper.
 *
 * When working directly with checksums, it's in our best interest to never
 * fire any hooks or generate derivatives. To prevent any issues (especially
 * race conditions resulting from the latter), we instantiate a base Tuque.
 *
 * @return RepositoryConnection
 *   A RepositoryConnection object containing a base api and repository.
 */
function islandora_checksum_get_tuque_connection() {
  $connection = &drupal_static(__FUNCTION__);
  if (!$connection) {
    // Get user info.
    global $user;
    if ($user->uid == 0) {
      $user_string = 'anonymous';
      $pass_string = 'anonymous';
    }
    else {
      $user_string = $user->name;
      $pass_string = $user->pass;
    }

    module_load_include('inc', 'islandora', 'includes/tuque');
    try {
      $serializer = new FedoraApiSerializer();
      $connection = new RepositoryConnection(variable_get('islandora_base_url', 'http://localhost:8080/fedora'), $user_string, $pass_string);
      $api = new FedoraApi($connection, $serializer);
      $connection->repository = new FedoraRepository($api, new SimpleCache());
    }
    catch (Exception $e) {
      drupal_set_message(t('Unable to connect to the repository %e', array('%e' => $e)), 'error');
    }
  }

  return $connection;
}

/**
 * Sets the checksums for an object's datastreams.
 *
 * Does so safely, without triggering datastream hooks or derivatives.
 *
 * @param string $pid
 *   The PID of the object the datastream belongs to.
 * @param array $dsids
 *   The DSIDs to set checksums for. Leave empty to use the configured defaults.
 * @param array|null $type
 *   The type of checksums to set. Leave NULL to use the configured default.
 *
 * @throws InvalidArgumentException
 *   If the object doesn't exist.
 */
function islandora_checksum_set_checksums($pid, $dsids = array(), $type = NULL) {
  if (is_null($type)) {
    $type = variable_get('islandora_checksum_checksum_type', 'DISABLED');
  }

  // Verify the datastream.
  $connection = islandora_checksum_get_tuque_connection();
  try {
    $object = $connection->repository->getObject($pid);
  }
  catch (Exception $e) {
    $message = t('Failed to load object %id.', array('%id' => $pid));
    throw new InvalidArgumentException($message, $e->getCode(), $e);
  }

  if (empty($dsids)) {
    $dsids = islandora_checksum_unpack_dsid_filter();
  }

  foreach ($dsids as $dsid) {
    if (isset($object[$dsid])) {
      // Set the checksum. We're not setting this on $object[$dsid] directly
      // because we're not guaranteed it's outside of the Islandora Tuque
      // wrapper.
      $connection->repository->api->m->modifyDatastream($pid, $dsid, array(
        'checksumType' => $type,
      ));
    }
  }
}
