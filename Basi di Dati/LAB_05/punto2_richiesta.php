<!DOCTYPE html>
<html lang="it" dir="ltr">
    <head>
        <meta charset="utf-8">
        <title>Punto 2 - Richiesta</title>
    </head>
    <body>
        <h1>Inserimento nuova programmazione/lezione</h1>
        <form action="punto2_risultato.php" method="post">
            <p>Programmazione della nuova lezione settimanale</p>
            <table>
                <tr>
                    <td>Istruttore:</td>
                    <td>
                        <select name="codice_istruttore">
                            <?php
                            // Connessione a MySQL
                            $con = mysqli_connect('localhost', 'root', '', 'PALESTRA');
                            if (mysqli_connect_errno()) {
                                die('Failed to connect to MySQL: '.mysqli_connect_error());
                            }
                            mysqli_set_charset($con,"utf8");

                            // Query
                            $sql = "SELECT CodFisc, Nome, Cognome
                                    FROM ISTRUTTORE
                                    ORDER BY Cognome, Nome";

                            $result = mysqli_query($con, $sql);

                            if (! $result) {
                                die('Query error: '.mysqli_error($con));
                            }

                            // Opzioni select
                            if (mysqli_num_rows($result) > 0) {
                                while ($row = mysqli_fetch_row($result)) {
                                    echo '<option value="'.$row[0].'">'.$row[2].' '.$row[1].' ('.$row[0].')'.'</option>';
                                }
                            }

                            // Chiusura connessione
                            mysqli_close($con);
                            ?>
                        </select>
                    </td>
                </tr>
                <tr>
                    <td>Giorno:</td>
                    <td><input type="text" size="10" maxlength="10" name="giorno"></td>
                </tr>
                <tr>
                    <td>Ora inizio:</td>
                    <td><input type="text" size="10" maxlength="10" name="ora_inizio"></td>
                </tr>
                <tr>
                    <td>Durata:</td>
                    <td><input type="text" size="10" maxlength="5" name="durata"></td>
                </tr>
                <tr>
                    <td>Corso:</td>
                    <td>
                        <select name="codice_corso">
                            <?php
                            // Connessione a MySQL
                            $con = mysqli_connect('localhost', 'root', '', 'PALESTRA');
                            if (mysqli_connect_errno()) {
                                die('Failed to connect to MySQL: '.mysqli_connect_error());
                            }
                            mysqli_set_charset($con,"utf8");

                            // Query
                            $sql = "SELECT CodC, Nome
                                    FROM CORSI
                                    ORDER BY Nome";

                            $result = mysqli_query($con, $sql);

                            if (! $result) {
                                die('Query error: '.mysqli_error($con));
                            }

                            // Opzioni select
                            if (mysqli_num_rows($result) > 0) {
                                while ($row = mysqli_fetch_row($result)) {
                                    echo '<option value="'.$row[0].'">'.$row[1].' ('.$row[0].')'.'</option>';
                                }
                            }

                            // Chiusura connessione
                            mysqli_close($con);
                            ?>
                        </select>
                    </td>
                </tr>
                <tr>
                    <td>Sala:</td>
                    <td><input type="text" size="10" maxlength="5" name="sala"></td>
                </tr>
            </table>
            <br>
            <input type="submit" value="Inserisci">
        </form>
    </body>
</html>
