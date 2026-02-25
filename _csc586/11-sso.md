---
layout: lecture
pretty_table: true
collection: csc586
course: CSC 586: Linux System Administration and Security - Summer 2024 - 100% online asynchronous
title: "Single Sign On"
toc:
  - name: Core SSO Elements
  - name: LDAP: Lightweight Directory Access Protocol
  - name: Structure of LDAP data
  - name: Common attribute names
  - name: Hands-on: update your webserver profile
  - name: 6: Hands-on: update and launch CloudLab
  - name: Hands-on: install and configure LDAP
  - name: Hands-on: Setup SSO on client
---

# Single Sign On

## Core SSO Elements

- A centralized directory store that contains user identity and 
authorization information.
- A tool for managing user information in the directory. 
- A mechanism for authenticating user identities. It could be the 
LDAP store itself, or a Kerberos ticket-based authentication system. 
- Centralized-identity-and-authentication-aware versions of the C library 
routines that look up user attributes. This is often configured through 
the name service switch file, `/etc/nsswitch.conf`.

---

## LDAP: Lightweight Directory Access Protocol

- Assumptions:
  - Data objects are relatively small.
  - The database will be widely replicated and cached.
  - The information is attribute-based.
  - Data are read often but written infrequently.
  - Searching is a common operation. 
- Common usage: A central repository for login names, passwords, and other account attributes. 

---

## Structure of LDAP data

- Property lists (entries). 
- Each entry consists of a set of named attributes along 
with those attributes’ values. 
- Every attribute can have multiple values. 
 

{% details Example attributes %}


~~~bash
dn: uid=ghopper,ou=People,dc=navy,dc=mil
objectClass: top
objectClass: person
objectClass: organizationalPerson
objectClass: posixAccount
objectClass: shadowAccount
uid: ghopper
cn: Grace Hopper
userPassword: {crypt}$1$pZaGA2RL$MPDJoc0afuhHY6k8HQFp0
loginShell: /bin/bash
uidNumber: 1202
gidNumber: 1202
homeDirectory: /home/ghopper
~~~

{% enddetails %}
---

## Common attribute names

| Attribute   | Stand for           | What it is            | 
| ----------- | ------------------- |-------------------------------------------------------------------------------------------| 
|      o      | Organization        | Identifies a site’s top-level entry (not used at sites that model their hierarchy on DNS) |
|      ou     | Organizational Unit | A logical subdivision, e.g. "marketing"                                                   |
|      cn     | Common name         | The most natural name to represent the entry                                              |
|      dc     | Domain component    | Used at sites that model their hierarchy on DNS                                           |
| objectClass | Object class        | Schema to which this entry's attributes conform                                           |

---

## Hands-on: update your webserver profile

- Create a new branch from `webserver` and call `webserver-ldap`. 

{% include figure.liquid path="assets/img/courses/csc586/11-sso/webserver-ldap.png" width="50%" zoomable=true %}

- Update `profile.py` to match the following content

<script src="https://gist.github.com/linhbngo/060f8a99fbc3666b6abf8f05be54a28c.js?file=profile-ldap.py"></script>

- Update and instantiate an experiment from this new branch.

---

## 6: Hands-on: update and launch CloudLab

- Create a new branch from `webserver` and call `webserver-ldap`. 

{% include figure.liquid path="assets/img/courses/csc586/11-sso/webserver-ldap.png" width="50%" zoomable=true %}

- Update `profile.py` to match the following content

<script src="https://gist.github.com/linhbngo/060f8a99fbc3666b6abf8f05be54a28c.js?file=profile-ldap.py"></script>

- Update and instantiate an experiment from this new branch.

---

## Hands-on: install and configure LDAP

- Connect into the `ldap` node and run the following commands

~~~bash
clear
sudo apt update
sudo apt install -y slapd ldap-utils
~~~

- Provide a (simple) password for LDAP server
  - Press the `Tab` key to go to `Ok`, then press `Enter`. 
  - Retype the password, then `Tab`, `Ok`, and `Enter` again. 

- Setup OpenLDAP server

~~~bash
sudo dpkg-reconfigure slapd
~~~

- Refuse to omit OpenLDAP server configuration
  - Keep the default `No` (or make sure that you stay on `No`), then 
  press `Enter`. 

- Enter `wcupa.edu` as default DNS domain name
  - Press the `Tab` key to go to `Ok`, then press `Enter`.

- Enter `wcupa.edu` as the name of the organization to use in the base DN
  - Press the `Tab` key to go to `Ok`, then press `Enter`.

- Enter the password (previously created) for your LDAP directory
  - Press the `Tab` key to go to `Ok`, then press `Enter`.

- Enter the password again for your LDAP directory
  - Press the `Tab` key to go to `Ok`, then press `Enter`.

- Select `Yes` to remove the database when `slapd` is purged. 
  - Press the `Tab` key to go to `Yes`, then press `Enter`.

- Select `Yes` to move old database
  - Press the `Tab` key to go to `Yes`, then press `Enter`.

- Enable firewall rules

~~~bash
sudo ufw allow ldap
~~~

- Create a file named `basedn.ldif` with the following contents

<script src="https://gist.github.com/linhbngo/060f8a99fbc3666b6abf8f05be54a28c.js?file=basedn.ldif"></script>

- Run the following command to populate LDAP.
  - Enter the password for LDAP previously created, then press Enter. 

~~~bash
ldapadd -x -D cn=admin,dc=wcupa,dc=edu -W -f basedn.ldif
Enter LDAP Password:
adding new entry "ou=People,dc=wcupa,dc=edu"

adding new entry "ou=Groups,dc=wcupa,dc=edu"

adding new entry "cn=CSC,ou=Groups,dc=wcupa,dc=edu"
~~~

- Run the following command to generate a password hash
  - The password is `rammy`

~~~bash
slappasswd
New password:
Re-enter new password:
{SSHA}N8Rfc9lvnKb8A3oUOxUOBlDen4v8FYL/
~~~

- Create a file named `users.ldif` using the following content
  - Replace the hash in `userPassword` field with the password hash you just created. 

<script src="https://gist.github.com/linhbngo/060f8a99fbc3666b6abf8f05be54a28c.js?file=users.ldif"></script>

- Populate LDAP with user info

~~~bash
ldapadd -x -D cn=admin,dc=wcupa,dc=edu -W -f users.ldif
Enter LDAP Password:
adding new entry "uid=student,ou=People,dc=wcupa,dc=edu"
~~~

- Test LDAP

~~~bash
ldapsearch -x -LLL -b dc=wcupa,dc=edu 'uid=student' cn gidNumber
dn: uid=student,ou=People,dc=wcupa,dc=edu
cn: student
gidNumber: 5000
~~~

---

## Hands-on: Setup SSO on client

- Connect to `webserver` node and run the following commands

~~~bash
clear
sudo apt update
sudo apt-get update
sudo apt install -y libnss-ldap libpam-ldap ldap-utils
~~~

- Configure `ldap-auth-config`
  - Based on the `profile.py`, `ldap` will have `192.168.1.3` as a predefined IP address. 
  - You can test by run `cat /etc/hosts` on `ldap`. 
  - Enter `ldap://192.168.1.3` as LDAP server Uniform Resource Identifier. 
    - **PAY ATTENTION TO ALL CHARACTERS**
  - Distinguished name of the search base: `dc=wcupa,dc=edu`
  - LDAP version to use: `3`
  - Make local root Database admin: `Yes`
  - Does the LDAP database require login? `No`
  - LDAP account for root: `cn=admin,dc=wcupa,dc=edu`
  - LDAP root account password: Use the password you created earlier
- Enable LDAP profile for NSS
  - Run `sudo nano /etc/nsswitch.conf`
  - Change the configurations of `passwd` and `group` to: `compat systemd ldap`
  - Save and quit
- Enable LDAP profile PAM
  - Run `sudo nano /etc/pam.d/common-password`
    - Find the line with the phrase `use_authtok` and delete that phrase
 - Run `sudo nano /etc/pam.d/common-session`
    - Add the following line to the end: `session optional pam_mkhomedir.so skel=/etc/skel umask=077`
- Test that now you can authenticate user `student` on `webserver` via LDAP

~~~bash
getent passwd student
student:x:10000:5000:Golden Ram:/home/student:/bin/dash
lngo@webserver:~$ su student
Password:
$
~~~

---
