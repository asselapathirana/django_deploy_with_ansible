#!/bin/bash
cp ../pass.yml .p.yml
ansible-vault decrypt --vault-password-file ~/.vault_pass.txt  .p.yml
awk '{if( $0 ~ /passw/){ $(NF)="xxxxx"}; print }' .p.yml > pass_ex.yml
rm -f .p.yml
