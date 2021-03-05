<?php
    include '../include/db_connect.php';

    $year = $_GET['year'];

    $sql = "SELECT ID_IS, ILName, COUNT(ID_IV), SUM(IAllCost)
            FROM `internet_provider`.`installer` 
            JOIN `internet_provider`.`invoice` USING(ID_IS)
            WHERE YEAR(IDate) = $year
            GROUP BY ID_IS;";

    try {
        $result = $pdo->query($sql);
    } catch(PDOException $e) {
        echo "Ошибка выполнения запроса! Возможно были введены некорректные данные!";
        include 'out_select_2.html';
        exit();
    }

    $rownumb = $result->rowcount();

    if ($rownumb) {
        $expenditures = $result->fetchAll();
    } else {
        echo "Сведения о работе монтажников за $year год нет!";
        include 'out_select_2.html';
        exit();
    }
?>

<html>
    <head> <title> Интернет провайдер </title> </head>
    
    <body bgcolor=silver>
        <h2> <?php echo "Сведения о работе монтажников за $year год."; ?> </h2> <br>
        <table border=1 width=60%>
            <tbody>
                <tr>
                    <td> Табельный номер </td>
                    <td> Фамилия </td>
                    <td> Общее количество накладных </td>
                    <td> Общая стоимость по накладным </td>
                </tr>

                <?php foreach($expenditures as $expenditure): ?>
                <tr>
                    <td> <?php echo $expenditure['ID_IS']; ?> </td>
                    <td> <?php echo $expenditure['ILName']; ?> </td>
                    <td> <?php echo $expenditure['COUNT(ID_IV)']; ?> </td>
                    <td> <?php echo $expenditure['SUM(IAllCost)']; ?> </td>
                </tr>
                <?php endforeach ?>
            </tbody>
        </table> <br>

        <?php include 'out_select_2.html'; ?>
    </body>
</html>