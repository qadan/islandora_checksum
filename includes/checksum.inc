<?php

/**
 * @file
 * Functionality for working with checksums in Fedora.
 */

/**
 * Modifies an existing object's datastream checksums.
 *
 * @param string $pid
 *   The PID of the object the datastream belongs to.
 * @param array $dsids
 *   The DSIDs to set checksums for. Leave empty to use the configured defaults.
 * @param string|null $type
 *   The type of checksums to set. Leave NULL to use the configured default.
 *
 * @throws InvalidArgumentException
 *   If the object doesn't exist.
 */
function islandora_checksum_set_checksums($pid, $dsids = array(), $type = NULL) { 
  $object = islandora_object_load($pid);
  if (!$object) {
    throw new InvalidArgumentException(t('The object %id does not exist.', array(
      '%id' => $pid,
    )));
  }

  if (empty($dsids)) {
    $dsids = islandora_checksum_unpack_dsid_filter();
  }
  if (is_null($type)) {
    $type = variable_get('islandora_checksum_checksum_type', 'DISABLED');
  }

  foreach ($dsids as $dsid) {
    if (isset($object[$dsid]) && $object[$dsid]->checksumType) {
      $object[$dsid]->checksumType = $type;
    }
  }
}
