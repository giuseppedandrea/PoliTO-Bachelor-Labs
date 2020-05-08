<!DOCTYPE html>
<html lang="it" dir="ltr">
    <head>
        <meta charset="utf-8">
        <title>Punto 2 - Richiesta</title>
    </head>
    <body>
        <h1>Ricerca lezioni istruttore</h1>
        <form action="punto2_risultato.php" method="post">
            Cognome istruttore:
            <select name="cognome_istruttore">
                <?php
                // Connessione a MySQL
                $con = mysqli_connect('localhost', 'root', '', 'PALESTRA');
                if (mysqli_connect_errno()) {
                    die('Failed to connect to MySQL: '.mysqli_connect_error());
                }
                mysqli_set_charset($con,"utf8");

                // Query
                $sql = "SELECT DISTINCT Cognome
                        FROM ISTRUTTORE
                        ORDER BY Cognome";

                $result = mysqli_query($con, $sql);

                if (! $result) {
                    die('Query error: '.mysqli_error($con));
                }

                // Opzioni select
                if (mysqli_num_rows($result) > 0) {
                    while ($row = mysqli_fetch_row($result)) {
                        echo '<option value="'.$row[0].'">'.$row[0].'</option>';
                    }
                }

                // Chiusura connessione
                mysqli_close($con);
                ?>
            </select>
            <br><br>
            Giorno della settimana:
            <select name="giorno_settimana">
                <option value="Lunedì">Lunedì</option>
                <option value="Martedì">Martedì</option>
                <option value="Mercoledì">Mercoledì</option>
                <option value="Giovedì">Giovedì</option>
                <option value="Venerdì">Venerdì</option>
                <option value="Sabato">Sabato</option>
                <option value="Domenica">Domenica</option>
            </select>
            <input type="submit" value="Cerca">
        </form>
    </body>
</html>
