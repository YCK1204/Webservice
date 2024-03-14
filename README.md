# Webservice
This program is a C++ single-threaded web service based on Mini Nginx.

Usage of Config Files

The program utilizes configuration files located in Config/*.conf as command-line arguments.

Each configuration file (*.conf) contains servers, and each server has associated location blocks.

For server member variables:

root_path
default_index_page_path
default_error_page_path (404)
client_body_size
listen (server port)
host
server_name
default_index_page_path and default_error_page_path together serve the file located at root_path + default_index_page_path.

client_body_size represents the maximum size allowed for the request body.

host denotes the address.

Location blocks include:

default_root
allow methods (GET, POST, DELETE)
autoindex (on, off)
default_index_page_path
return path (301)
cgi-path
default_root represents the domain.

autoindex displays all files and directories in server's root_path + default_root_path.

return path redirects to the location block with the corresponding default_root_path. If the block doesn't exist, it triggers a 404 error.

default_index_page_path is used as root_path + default_index_page_path.

cgi-path opens a window with CGI functionality, appended to root_path.

Multiple servers can be launched using different ports. Access through a web browser by entering localhost:port/desired_location_root in the address bar.

Program Usage

Run make.

Execute ./webserv argument, where argument is the configuration file. If no argument is provided, it defaults to ./Config/default.conf.
