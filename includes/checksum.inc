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
 *   The DSIDs to set checksums for. Leave empty to set on all datastreams.
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

  if (is_null($type)) {
    $type = variable_get('islandora_checksum_checksum_type', 'DISABLED');
  }

  if (empty($dsids)) {
    foreach ($object as $datastream) {
      if ($datastream->checksumType != $type) {
        $datastream->checksumType = $type;
      }
    }
  }
  else {
    foreach ($dsids as $dsid) {
      if (isset($object[$dsid]) && $object[$dsid]->checksumType != $type) {
        $object[$dsid]->checksumType = $type;
      }
    }
  }
}
