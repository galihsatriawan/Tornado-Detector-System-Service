<?php 
    include 'database_handler.php'; 
    $fields = array();
    $params = array();
    $values = array();
    
    $arduino = select_data("tb_mst_arduino",$fields,$params,$values);
    print_r($arduino);
    echo    "Hello";
?>