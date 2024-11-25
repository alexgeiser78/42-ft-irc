container:
	is a group constitued by an app and his dependencies(librairiy, configurations...) isolated in his environnement. Permits to work on a computer a server or cloud. (Light, fast).
	
VM: 	
	is a isolated environment used to make work an os. It's a computer inside a computer
	
Difference: container share a common "noyau", a VM has is own OS.

Docker: 
	tool used to create and manage application in containers
Image Docker:
	model containing all necessary to execute an app
Docker container:
	instance in curse of execution of the docker image
Docker engine:
	motor who's manage the containers and image. It contain a deamoon who manages the execution and an interface in command line to interact with docker.
	
Docker compose:
	is a tool used to manage multiple containers and images. it uses a docker-compose.yml file
	
diff between a docker image used with docker compose and without:
	-without: 
		1 container
		manual conf without docker-compose file ()
	-with:
		multiple container
		automatic conf
advantages of docker comparing to VM:
	docker:
		light
		fast start
		better use of CPU and mem, multiple container can share the sames resscources
		fully portable
		a bit less isolated than VM 
		easy to manage with docker-compose
		easy to upgrade, add containers
	VM:
		heavy(full OS)
		slow, load of the full OS
		use of the complete ressources
		portable but depending on the main OS
		fully isolated
		harder to manage, update...
		harder to upgrade
		
check: 		
	curl -I http://ageiser.42.fr
	curl -I https://ageiser.42.fr
	
SSL/TLS
	openssl s_client -connect example.com:443
	curl -v https://ageiser.42.fr
	
docker compose ls
docker compose ps
docker volume ls
docker volume inspect mariadb


connect to the db:
	docker exec -it mariadb /bin/bash/
	mysql -u root -p
	USE wordpress_db;
	SHOW TABLES;
	


docker network:
		connect multiple containers together	
		
Fast CGI:
	protocole of communication that allows to a web server(nginx) to communicate with external app(WP and MDB) fast because the process is memorised
	
PHP-FPM:
	implementation of PHP to manage Fast CGI
	
what is TLS:
	transport layer security to encrypt the communications between a server and a client
	
openssl:
	open source librairy that can handle comuications with ssl/tls
	
	
clean:
	docker stop $(docker ps -qa); docker rm $(docker ps -qa); docker rmi -f $(docker images -qa); docker volume rm $(docker volume ls -q); docker network rm $(docker network ls -q) 2>/dev/null

