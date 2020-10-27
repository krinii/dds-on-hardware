---
title: Meetings with Tórur
created: '2020-03-04T08:39:24.760Z'
modified: '2020-10-27T08:41:19.251Z'
---

# Meetings with Tórur

## 4/3 - 2020
Find ROS2 mail list
memoir
pdf latex - tex live

## 11/3 - 2020
2 docker (controller)(computer)
test dds between docker containers
understand **namespaces** and **contorl groups** in linux
learn dockerfile
make log of work

## 29/7
### Questions
Har jeg et budget
Skal jeg have et budget i rapporten
Skal jeg have et tids skema over hvornår jeg har lavet hvad

### Notes
- Varnish (caching tool/method)
  - https://varnish-cache.org/intro/index.html#intro
- Evt. gem noget af dataen på en sd eller hdd
- Lav Kravspecifikation (Requirements Specification)
- Lav backup system/ Version control

## 18/8

Jeg fandt dockerfile. Det var det forkerte workspace, det er rigtige var ros2-micro i Master_Project. 
*/home/k/Desktop/Workspaces/Master_Project/ros2-micro/ros2-micro-dev-environment/.devcontainer*

Opsætning af dropbox på linux

### Notes
Local git server (into private github with student licsense)

## 1/9
### Questions
How can I obsver the communication between the pi's. (Can wireshark do it?)

### Notes

dmesg (wifi dongle)
laptop some bridge
transparrent firewall
tcp dump

rød tråd i krav sp
beskriv testene

## 15/9

### Notes
Hvad kræver det at stætte pi'sne op (husk at nævne alt der har været en del af projeket)

strace (hvilke filer et progam accesser)

reconnector it device til netwærket hvis det bliver fra koblet.

lave requriement baseret på mir's behove

test dårligt netwærk

hvordan virker historien.

Hvilke ting vill du test i qos, skriv det ind i krævspecifikation.

Hvilken scalabllity har dds. Hvor meget press kan det håndtere (hvad er dets throughput, er det begrænset af processer kraft, netværket eller noget andet.)

ss -p opensockets (til at finde programmet som bliver ved med at lave et dns kald)

## 29/9-2020

### Questions
Hvordan kan man dokumenter test som f.eks. history size

### Notes
* Programmer til at teste funktionaliteten af test programmeren under stress:
  * stress-ng (hardware stress)
  * iperf (netværk stress)

* Nogle af testene skal laves for at på vise at lovede funktinoalit virker som lovet.

* Slet/omskriv del omkring at bruge TCP eller UDP, bør bare laves om til at bruge best effort og reliable.

* Forklar hvor "kravne" i problem analysen kommer fra, var det noget du snakkede med MiR om (hvorfor bruger du den MCU?) (de kan ikke bare komme fra den blå luft)

## 22/10-2020

### Questions
* Hvordan skal jeg dokumenter mine resulater, der kommer ikke lige frem tal ud.
* Burde jeg bruge scripts til at udføre testene for at ens svar.
* Problemet med at reader nogle gange spammer "New Read" print'ed

### Notes
 * Beskeder per "tid" på forskillig hardware (skriv til samme device)
 * (Egnen tanke) Skriv om hvordan DDS opfylder kravene i kravspecifikation, du behøver nok ikke at teste dem. Fokuser på hvad dds specifikation kræver og ikke på en implementering i denne del.
 * Du skal nok have lidt om security i dds.

 ## 27/10-2020

 ### Question
  * Snak lidt om de captures du fik ud af wireshark når du sendte data over loopback.
  * Burde jeg udføre nogle test ved brug af loopback i stedet for devicets wifi modul?
  * Snak om de ændring du have lavet i performs test afsnittet, er strukturen som den skal være?
  * Er testene gode nok, mangler der noget, burde der være flere?
  * Snak lidt om talene fra read/write speed. 
  * Burde jeg udføre mere statestic på mine tal. Foreksample histogram?
  * Burde jeg lave mere end 100 cycles. På histogram'et kunne det godt se ud som om det ville give en pænere bell-kurve, men er det nødvendigt?

  ### Notes
  
