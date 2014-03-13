## Islandora Checksum

### Build Status

[![Build Status](https://travis-ci.org/Islandora/islandora_checksum.png?branch=7.x)](https://travis-ci.org/Islandora/islandora_checksum)

### SUMMARY

A simple module to allow repository managers to enable the creation of a checksum for objects. If enabled, the following checksum algorithms are available: MD5, SHA-1, SHA-256, SHA-384, SHA-512. 

**Note**: This is will checksum all datastreams.

### INSTALLATION

Same as any Drupal module. There are no prerequisites other than Islandora. 

```
$ cd $DRUPAL_ROOT/sites/all/modules
$ git clone https://github.com/islandora/islandora_checksum
$ drush pm-enable islandora_checksum
```

### Configuration

Go to admin/islandora/checksum and turn on checksum creation, and select the checksum algorithm you would like to use. If you would like to retroactively enable checksums on existing objects, choose a collection and click on the 'Enable' button.

[![Configuration](http://i.imgur.com/1S92cgQ.png)](http://i.imgur.com/1S92cgQ.png)

### License

[GPLv3](http://www.gnu.org/licenses/gpl-3.0.txt)

### Thanks

[Adam Vessey](https://github.com/adam-vessey)

[Jonathan Green](https://github.com/jonathangreen)

[Jordan Dukart](https://github.com/jordandukart)
