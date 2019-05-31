FROM httpd:2.4
COPY ./docs/html/ /usr/local/apache2/htdocs/
