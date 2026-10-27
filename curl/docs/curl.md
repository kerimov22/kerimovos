# curl — KerimovOS HTTP client

Binary: /opt/curl/curl
Sources: /opt/curl/src/
Symlink: /bin/curl -> /opt/curl/curl

Usage:
  curl [-o file] [-O] [-I] [-L] [-s] [-v] [-H header] URL

Examples:
  curl http://example.com/
  curl -O http://example.com/file.txt
  curl -I http://example.com/
  curl -L -s http://example.com/

Notes:
  - Only http:// is supported. https:// returns: curl: (35) SSL/TLS not supported yet.
  - Progress bar in pacman/curl style.
