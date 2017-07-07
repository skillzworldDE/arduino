## Hallo und Willkommen 

Auf meinen Seiten will ich Euch die verschiedensten Projekte und Programmschnipsel vorstellen, welche sich im Laufe der Jahre so bei mir gesammelt haben. Vielleicht findet sich ja die eine oder andere Anregung für dein nächstes Projekt, oder aber du meinst eine bessere Lösung zu haben, dann erzähl mir davon. Ich lerne gerne dazu.


### Hier geht es um den Arduino

In diesem Repository geht es um den Arduino. Lange Zeit habe ich nichts von ihm wissen wollen (hielt ihn für Spielzeug), doch seit kurzem beschäftige ich mich nun doch damit. Durch ein "schnelles" Projekt für einen Freund bin ich dazu gekommen. 

Nun bin ich noch lange kein Profi und arbeite (noch) mit der Arduino IDE und dem C-Syntax, also nicht zu viel erwarten. :)

### Alles für ein Projekt

Zur Zeit arbeit ich mich ja wie gesagt noch ein. Da ich gerne wandere sollte mein erstes Projekt ein nützlicher Helfer für diesen Zeitvertreib werden. Dank ebay fanden sich schnell alle Komponenten. Alles wurde verlötet und in ein kleines Gehäuse gepackt und will nun programmiert werden....

Name des Projektes: "Hikers Helper" (Wander-Helfer)
Was hat er? Was kann er?
- Handgerät mir Li-Ion Akku, Laderegler und StepUp Wandler
- auf Basis des Arduino Nano
- 1,8'' Display + 4 Tasten als Userinterface
- Erfassung und Speicherung von:
  1. Position (GPS)
  2. Temperatur und Luftdruck (BMP180)
  3. Höhe (Barometrisch + GPS)
  4. Kompass (Gyroskop und Magnetisch) mit Tilt-Kompensation
- Speichermedium SD-Card
- Datenübertragung via Bluetooth zu optionaler Android-App
- RTC (DS1307)


Die in diesem Repository gesammelten Code-Schnipsel dienen alle der Erfüllung einer Teilaufgabe aus diesem Projekt. So scheint manches Codefragment gelegentlich sinnlos zu sein, da es kompfortablere Bibliotheken gibt die die selbe Aufgabe erledigen. Aber im Gesamtprojekt gab es immer wieder Gründe warum ich es anders gemacht habe:

- Speicherplatzmangel (manche Bibliotheken tragen einfach zu dick auf)
- Timing (Geschwindigkeit und Interrupts sollten optimiert werden)
- Pinout (Manche Bibliotheken setzte bestimmte Pins voraus, das war oft nicht machbar)
- persönliche Ansprüche

Schaut euch gerne etwas um wenn ihr wollt....
