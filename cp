#!/bin/bash
cp ../pass.yml .p.yml
python2 `which ansible-vault` decrypt --vault-password-file ~/.vault_pass.txt  .p.yml
awk '{if( $0 ~ /passw/){ $(NF)="xxxxx"}; print }' .p.yml > pass_ex.yml
rm -f .p.yml
cat $VIRTUAL_ENV/bin/postactivate | sed 's/=[^=]*$//' > postactivate
cat $VIRTUAL_ENV/bin/predeactivate | sed 's/=[^=]*$//'> predeactivate
 
