# Arduino-Proiect-Final
 Masinuta controlata prin Wi-fi ( sau MCWi )
 MCWi este un robotel care poate fi controlat de la distanta pentru a explora imprejurimile , a spiona sau de a ajunge in locuri inaccesibile datorita dimensiunii sale relativ mici , in timp ce face broadcasting live .
 
 Partea Fizica . MCWi este alcatuit din doua motoare DC ce actioneaza doua rotite in mod independent, pe care le controlam cu ajutorul unui driver de motoare si a unei placute Arduino Uno . Comunicarea wi-fi se realizeaza printr-un modul ESP8266. Broadcasting-ul va fi asigurat de un telefon pe care il atasam robotului . 
 
 Partea Logica . Modulul Wi-Fi legat la Arduino il conectam la o retea Wi-fi si incepem un web server pe portul 80 printr-un anumit set de comenzi care le trimitem modulului . In acelasi timp conectam un laptop la acel web server prin Telnet , si dintr-o pagina pagina html trimitem la acel server, prin sageti , comenzi pentru a controla directia robotului si sunt preluate de modulul Wi-fi de pe arduino si interpretate . In acelasi timp in telefon pornim aplicatia IP Webcap care va incepe sa filmeze si sa trasmita datele pe un anume server , iar noi tot ce trebuie sa facem este sa luam acele date video si audio si sa le implementam in pagina noastra web .
 
  Link catre BOM https://docs.google.com/spreadsheets/d/1BSJHzgeDrs-UPZU2LdOBcqGRzRCHHSMtwE_--AWlk6M/edit?usp=sharing

