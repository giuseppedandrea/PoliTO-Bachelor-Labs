<!DOCTYPE html>
<html lang="it" dir="ltr">
    <head>
        <meta charset="utf-8">
        <title>Punto 3 - Risultato</title>
    </head>
    <body>
        <?php
        // Controllo parametri POST
        if (! isset($_REQUEST["codice_corso"])) {
            die('Inserire tutti i dati richiesti');
        }
        $codice_corso = $_REQUEST["codice_corso"];

        // Connessione a MySQL
        $con = mysqli_connect('localhost', 'root', '', 'PALESTRA');
        if (mysqli_connect_errno()) {
            die('Failed to connect to MySQL: '.mysqli_connect_error());
        }
        mysqli_set_charset($con,"utf8");

        // Header pagina
        echo "<h1>Lezioni in programma per il corso $codice_corso</h1>";
        echo "<h3>Le lezioni in programma il corso $codice_corso sono le seguenti.</h3>";

        // Query SQL
        $sql = "SELECT P.Giorno, P.OraInizio, P.Durata, P.Sala, I.Nome AS 'Nome Istruttore', I.Cognome AS 'Cognome Istruttore'
                FROM PROGRAMMA P, ISTRUTTORE I
                WHERE P.CodFisc=I.CodFisc AND
                      P.CodC='$codice_corso'";

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
            echo "Nessuna lezione in programma per il corso $codice_corso";
        }

        // Chiusura connessione
        mysqli_close($con);
        ?>

        <br>

        <form action="punto3_richiesta.php" method="post">
            <input type="submit" value="Effettua un'altra ricerca">
        </form>
    </body>
</html>
