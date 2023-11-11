# shellrealm
A Linux based Command & Control (C2) framework with a focus on bordem

C2 Framework Design:

* Access Payload will allow us to break into the machine
* Rootkits can be obfuscated before being planted onto the machine

```
+-----------+      +---------+      +----------------------+      +-------------------+
| C2 Server | ---> | Rootkit | ---> | Encryptor/Obfuscator | ---> | Victim's Computer |
+-----------+      +---------+      +----------------------+      +-------------------+
     |                                                                      /\
     |                                                                      /
     |                                                                     /
     +----------------> Access Payload Exploit ---------------------------+
```
also its kinda wip rn...
