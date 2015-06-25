Works with both python2 and python3 

Doesnot work with configurations where wsgi.py, staticroot etc. are in non-standard places (then need manual tweaking)

# django_deploy_with_ansible
Implementing on an Ubuntu VPS
: at the development node:
 -  Consider upgrading ansible to latest version (>1.8 was needed) using ppa:ansible/ansible 

#how to add this repository to a django-project
1. at the django project directory  
 git clone  <git remote url ending with .git> deploy

2. edit files ../development and ../pass.yml (if pass.yml is encrypted use ./ed ../pass.yml)
(if there are no such files in the django project, copy from the templates provided in this drectory)
 important: 
	1. application_directory variables will be used to create the application's directory. Make sure it is unique (from other, already installed apps in the server.) to avoid accidental overwrite. 
        2. application_name should match with your django app (directory wehre settigns.py lives!). 

=======

ssh-keygen -f "/home/pathirana/.ssh/known_hosts" -R  <host> 

# if the vps is minimal, there might be the need to manually login and install python (2.7), sshkey and sudo on remote machines
# login to the remote and 
apt-get update
apt-get install python-minimal sudo python-pip

3.  you have to make sure database and STATICFILES settings in django settings file should be, so:
    DATABASES = {
        'default': {
            'ENGINE': 'django.db.backends.postgresql_psycopg2',
            'NAME': os.getenv('DATABASE_NAME', 'anyname'),
            'USER': os.getenv('DATABASE_USER', 'anyname'),
            'PASSWORD': os.getenv('DATABASE_PASSWORD', 'password'),
            'HOST': os.getenv('DATABASE_HOST', '127.0.0.1'),
            'PORT': os.getenv('DATABASE_PORT', '5432'),
        }
    }    

   STATIC_ROOT = os.path.abspath(os.path.join(BASE_DIR, '../static'))
   # ../static part might need tweaking depending on django directory structure



#create user remoteuser
ansible-playbook -i development sshkey.yml -u root  --vault-password-file ~/.vault_pass.txt
(or use ./setkey)
#This user should be able to login and sudo without password

ansible-playbook -i development  site.yml --vault-password-file ~/.vault_pass.txt 
(or use ./setup)

at this stage optionally, the ./adhoc command could be run. This command will copy ../adhoc.yml and run it. ../adhoc.yml can contain custom commands that may be needed to run after installation

# ssl certificate
1. Create a ssl certificate (e.g. Using StartSSL) and download it (ssl.key.encyrpted). Download certificate as ssl.crt.mine
2. Decrypt the private key by using the password you entered when you created your key:
openssl rsa -in ssl.key.encrypted -out /etc/nginx/conf/ssl.key
3. download the signers certificte
wget http://www.startssl.com/certs/sub.class1.server.ca.pem
cat it together with ssl.crt.mine
cat ssl.crt.mine sub.class1.server.ca.pem > /etc/nginx/conf/ssl.crt 

Now point to these two files (ssl.key, ssl.crt) in ../pass.yml (ssl_key_file, ssl_crt_file)

# Caution with passwords etc. 
1. Careful not to use characters with special meaning on unix in passwords (e.g. $) -- nasty errors (e.g. can not login to the database?)
2. consider using django-sslify to enforce ssl. 
 (see special configuration needed in nginx and requirement to add SECURE_PROXY_SSL_HEADER = ('HTTP_X_FORWARDED_PROTOCOL', 'https')  to settings file)


# Elasticsearch

manually configure elasticsearch to use small memory. 

http://blog.lavoie.sl/2012/09/configure-elasticsearch-on-a-single-host.html

