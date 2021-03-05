<?php
    include '../include/db_connect.php';

    $year = $_GET['year'];

    $sql = "SELECT ID_LEP, LEPName, COUNT(ID_IV), SUM(LEPCost)
            FROM `internet_provider`.`expenditure` 
            JOIN `internet_provider`.`invoice` USING(ID_IV) 
            JOIN `internet_provider`.`lexpenditure` USING(ID_LEP)
            WHERE YEAR(IDate) = $year
            GROUP BY ID_LEP;";

    try {
        $result = $pdo->query($sql);
    } catch(PDOException $e) {
        echo "������ ���������� �������! �������� ���� ������� ������������ ������!";
        include 'out_select_1.html';
        exit();
    }

    $rownumb = $result->rowcount();

    if ($rownumb) {
        $expenditures = $result->fetchAll();
    } else {
        echo "�� $year ��� �� ���� ������� �� ������ ������ ������������!";
        include 'out_select_1.html';
        exit();
    }
?>

<html>
    <head> <title> �������� ��������� </title> </head>
    
    <body bgcolor=silver>
        <h2> <?php echo "�������� � ������� ������������ �� $year ���."; ?> </h2> <br>
        <table border=1 width=60%>
            <tbody>
                <tr>
                    <td> ���������� ���� </td>
                    <td> �������� </td>
                    <td> ����� ���������� � ������� </td>
                    <td> ����� ��������� </td>
                </tr>

                <?php foreach($expenditures as $expenditure): ?>
                <tr>
                    <td> <?php echo $expenditure['ID_LEP']; ?> </td>
                    <td> <?php echo $expenditure['LEPName']; ?> </td>
                    <td> <?php echo $expenditure['COUNT(ID_IV)']; ?> </td>
                    <td> <?php echo $expenditure['SUM(LEPCost)']; ?> </td>
                </tr>
                <?php endforeach ?>
            </tbody>
        </table> <br>

        <?php include 'out_select_1.html'; ?>
    </body>
</html>