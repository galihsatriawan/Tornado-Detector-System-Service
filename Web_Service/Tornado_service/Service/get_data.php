
<?php
include 'database_handler.php';

// echo "$date";
// $sql = "SELECT * FROM tb_mst_data td,tb_mst_arduino ta WHERE td.id_arduino = ta.id_arduino ORDER BY id_data DESC LIMIT 1";
// 	$var_1 = query_biasa($sql);
// 	print_r($var_1[0]);
// if($_SERVER['REQUEST_METHOD'] == 'POST'){
if(true){
	$sql = "SELECT * FROM tb_mst_data td,tb_mst_arduino ta WHERE td.id_arduino = ta.id_arduino ORDER BY id_data DESC LIMIT 1";
	$var_1 = query_biasa($sql);

	
	$respon['var_1']= $var_1[0]['var_1'];
	$respon['var_2']= $var_1[0]['var_2'];
	$respon['var_3']= $var_1[0]['var_3'];
	$respon['var_4']= $var_1[0]['var_4'];
	// $respon['var_5']= $var_1[0]['var_5'];
	$respon['lokasi'] = $var_1[0]['lokasi'];
	$respon['indication'] = $var_1[0]['indication'];
	
	
	echo json_encode($respon);
	
}else{

		$respon["status"] = "ok";
		$respon["json_api_version"]="0.0.1";
		echo json_encode($respon);
}
?>