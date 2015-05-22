# django_deploy_with_ansible

#how to add this repository to a django-project
#need the directory ansible-deploymnet at top level with file pass.yml in ansible-deployment/env_vars directory
# go to ansible-deployment directory and 
git clone  <git remote url ending with .git>  .

 

Implementing on an Ubuntu VPS
: at the development node:
 -  Consider upgrading ansible to latest version (>1.8 was needed) using ppa:ansible/ansible 
: 
2. edit files ./development and ./env_vars/pass.yml
(./ed env_vars/pass.yml and change the root password (supassword). )

ssh-keygen -f "/home/pathirana/.ssh/known_hosts" -R  <host> 

# if the vps is minimal, there might be the need to manually login and install python (2.7), sshkey and sudo on remote machines
# login to the remote and 
apt-get update
apt-get install sshkey python-minimal sudo pip


#create user remoteuser
ansible-playbook -i development sshkey.yml -u root  --vault-password-file ~/.vault_pass.txt
(or use ./setkey)
#This user should be able to login and sudo without password

ansible-playbook -i development  site.yml --vault-password-file ~/.vault_pass.txt 
(or use ./setup)
