# curl — KerimovOS HTTP Client

## Location
Binary: /opt/curl/curl
Sources: /opt/curl/src/
Symlink: /bin/curl -> /opt/curl/curl

## Usage

```
curl [options] URL

Options:
  -o FILE     Write output to FILE
  -O          Save remote file with original name
  -I          Show HTTP headers only
  -L          Follow redirects
  -s          Silent mode (no progress bar)
  -v          Verbose mode
  -H HEADER   Custom HTTP header
  --progress-bar  Show progress bar
```

## Examples

```
curl http://example.com/
curl -O http://example.com/file.txt
curl -I http://example.com/
curl -L -s http://example.com/
curl -H "Accept: text/html" http://example.com/
```

## Progress Display
```
[######################] 100%
```

## Notes
- Only http:// is supported
- https:// returns: curl: (35) SSL/TLS not supported yet
- Progress bar in pacman/curl style
