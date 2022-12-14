## DESCRIZIONE:
Il progetto consiste in una scena 3D navigabile mediante l'uso di mouse e tastiera.
Nella scena sono presenti diversi modelli, alcuni creati assemblando primitive e altri importando modelli _.OBJ_.
È possibile interagire con la scena, andando a **modificare materiale e tipo di shading** di ogni mesh non importata. È possibile anche andare a **spostare**, **ridimensionare**, **ruotare** questi modelli.
Gli alberi possono essere **eliminati** dalla scena cliccandoci 3 volte con il tasto destro del mouse.
Sono gestite le collisioni fra oggetto e telecamera mediante l'utilizzo delle bounding box.

## COMANDI:
- W-A-S-D: movimento della telecamera
- SPAZIO - D: movimento verticale della telecamera
- R: reset della posizione della telecamera alla posizione di default
- ESC: chiusura del gioco
- MOUSE TASTO SINISTRO: rotazione della telecamera attorno al target
- MOUSE TASTO DESTRO: permette di danneggiare un gli alberi della scena. Dopo 3 colpi, verranno eliminati
- CTRL + MOUSE TASTO DESTRO: seleziona un oggetto della scena per trasformarlo o cambiare shader
- MOUSE TASTO CENTRALE: apre menù per cambiare shading, materiale o visualizzare wireframe
- G, r, S: sposta, ruota e scala una mesh selezionata
- \+ o \-: cambia il fattore di movimento, rotazione o scalatura


## ISTRUZIONI PER LA COMPILAZIONE:  
Come nelle lezioni di laboratorio, è necessario copiare i file nella cartella del progetto e aggiungere i .cpp ai file di origine e i .h ai file di intestazione.
È necessario installare nupengl e glm dalla console nuget.
È anche necessario installare la libreria ASSIMP.
