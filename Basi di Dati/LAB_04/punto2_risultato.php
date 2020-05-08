<!DOCTYPE html>
<html lang="it" dir="ltr">
    <head>
        <meta charset="utf-8">
        <title>Punto 2 - Risultato</title>
    </head>
    <body>
        <?php
        // Controllo parametri POST
        if (! isset($_REQUEST["cognome_istruttore"]) || ! isset($_REQUEST["giorno_settimana"])) {
            die('Inserire tutti i dati richiesti');
        }
        $cognome_istruttore = $_REQUEST["cognome_istruttore"];
        $giorno_settimana = $_REQUEST["giorno_settimana"];

        // Connessione a MySQL
        $con = mysqli_connect('localhost', 'root', '', 'PALESTRA');
        if (mysqli_connect_errno()) {
            die('Failed to connect to MySQL: '.mysqli_connect_error());
        }
        mysqli_set_charset($con,"utf8");

        // Header pagina
        echo "<h1>Lezioni in programma</h1>";
        echo "<h3>Le lezioni in programma per l'istruttore $cognome_istruttore nel giorno $giorno_settimana sono le seguenti.</h3>";

        // Query SQL
        $sql = "SELECT P.Giorno, P.OraInizio, P.Durata, P.Sala, C.Nome AS 'Nome Corso', C.Tipo AS 'Tipo Corso', C.Livello AS 'Livello Corso', I.CodFisc AS 'Codice Fiscale Istruttore', I.Nome AS 'Nome Istruttore', I.Cognome AS 'Cognome Istruttore'
                FROM PROGRAMMA P, CORSI C, ISTRUTTORE I
                WHERE P.CodC=C.CodC AND
                      P.CodFisc=I.CodFisc AND
                      I.Cognome='$cognome_istruttore' AND
                      P.Giorno='$giorno_settimana'
                ORDER BY I.CodFisc, C.Nome";

        $result = mysqli_query($con, $sql);

        if (! $result) {
            die('Query error: '.mysqli_error($con));
        }

        // Creazione tabella
        if (mysqli_num_rows($result) > 0) {
            echo "<table border=1 cellpadding=10>";

            // Intestazione
            echo "<tr>";
            for ($i = 0; $i < mysqli_num_fields($result); $i++) {
                $field = mysqli_fetch_field($result);
                $name = $field->name;
                echo "<th>$name</th>";
            }
            echo "</tr>";

            // Righe tabella
            while ($row = mysqli_fetch_row($result)) {
                echo "<tr>";
                for ($i=0; $i < mysqli_num_fields($result); $i++) {
                    echo "<td>$row[$i]</td>";
                }
                echo "</tr>";
            }

            echo "</table>";
        } else {
            echo "Nessuna lezione in programma per l'istruttore $cognome_istruttore il giorno della settimana $giorno_settimana";
        }

        // Chiusura connessione
        mysqli_close($con);
        ?>

        <br>

        <form action="punto2_richiesta.php" method="post">
            <input type="submit" value="Effettua un'altra ricerca">
        </form>
    </body>
</html>
