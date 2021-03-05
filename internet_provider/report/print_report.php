<?php
    include '../include/db_connect.php';

    $year = $_GET['year'];
    $month = $_GET['month'];

    $sql = "SELECT *
            FROM `internet_provider`.`report`
            WHERE R_Year = $year AND R_Month = $month;";

    try {
        $result = $pdo->query($sql);
    } catch(PDOException $e) {
        echo "������ ���������� �������. �������� ���� ������� ������������ ������!";
        include 'out_print_report.html';
        exit();
    }

    $rownumb = $result->rowcount();

    if ($rownumb) {
        $reports = $result->fetchAll();
    } else {
        echo "������ �� ��������� ������ ������� �����������!";
        include 'out_print_report.html';
        exit();
    }
?>

<html>
    <head> <title> �������� ��������� </title> </head>
    
    <body bgcolor=silver>
        <h2> ����� ������ </h2> <br>
        <table border=1 width=60%>
            <tbody>
                <tr>
                    <td> ��� </td>
                    <td> ����� </td>
                    <td> �������� ������ </td>
                    <td> ���������� ����������� ����� </td>
                    <td> ����� ����� �� ����������� ������ </td>
                </tr>

                <?php foreach($reports as $report): ?>
                <tr>
                    <td> <?php echo $report['R_Year']; ?> </td>
                    <td> <?php echo $report['R_Month']; ?> </td>
                    <td> <?php echo $report['R_Name']; ?> </td>
                    <td> <?php echo $report['R_Count']; ?> </td>
                    <td> <?php echo $report['R_Sum']; ?> </td>
                </tr>
                <?php endforeach ?>
            </tbody>
        </table> <br>

        <?php include 'out_print_report.html'; ?>
    </body>
</html>