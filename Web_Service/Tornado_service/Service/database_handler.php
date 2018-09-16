<?php
	 $GLOBALS['conn'] = null;
	 
	 
	function pdo_connect(){

		$server = "localhost";
		$user = "gokil";
		$pass = "gokil";
		$dbname = "db_tornado";

		try {
			$conn = new PDO("mysql:host=$server;dbname=$dbname",$user,$pass);
			$conn->setAttribute(PDO::ATTR_ERRMODE,PDO::ERRMODE_EXCEPTION);
			// echo("Success Connect");
		} catch (Exception $e) {
			// echo $e.getMessage();
			die("Connection failed :".$e.getMessage());
		}

		return $conn;
	}

	function select_data($tb_name,$fields,$params,$values){
		try{
			if($GLOBALS['conn']==null){
				$GLOBALS['conn'] = pdo_connect();
			}
			$conn=$GLOBALS['conn'];
			//jadikan field dalam bentuk string
			$str_fields= convert_field_to_str($fields);
			if(count($params)==0){
				$sql = "SELECT ".$str_fields." FROM ".$tb_name;
				$prepare_query = $conn->prepare($sql);
				$prepare_query->execute();

			}else{
				$str_params = convert_params_to_str($params);
				$sql = "SELECT ".$str_fields." FROM ".$tb_name." WHERE ".$str_params;
				
				$prepare_query = $conn->prepare($sql);
				//Binding
				for($i=0;$i<count($params);$i++){
					$prepare_query->bindValue(":".$params[$i],$values[$i]);	
				}
				$prepare_query->execute();
				
			}
			$hasil = $prepare_query->fetchAll();
		} catch (Exception $e) {
			echo $sql."<br>".$e.getMessage();		
		}
		return $hasil;
	}

	function select_jumlah($tabel,$values){
		try{
			if($GLOBALS['conn']==null){
				$GLOBALS['conn'] = pdo_connect();
			}
			$conn=$GLOBALS['conn'];
			//jadikan field dalam bentuk string
			
			if ($values!=0) {
				$sql = "SELECT count(*) FROM ".$tabel." WHERE kode_user = '".$values."'";
				// echo($sql);
				$prepare_query = $conn->prepare($sql);
				$prepare_query->execute();
			} else {
				$sql = "SELECT count(*) FROM ".$tabel;
				// echo($sql);
				$prepare_query = $conn->prepare($sql);
				$prepare_query->execute();
			}
			
				
				
			
			$hasil = $prepare_query->fetchAll();
		} catch (Exception $e) {
			echo $sql."<br>".$e.getMessage();		
		}
		return $hasil[0][0];
	}

	// insert_data_with_several_field
	function insert_data($tb_name,$fields,$values){
		
		//jadikan field dalam bentuk string
		try {
			if($GLOBALS['conn']==null){
				$GLOBALS['conn'] = pdo_connect();
			}
			$conn=$GLOBALS['conn'];
							
	 		$str_fields= convert_field_to_str($fields);
			$str_values = convert_values_to_str($values); 

			$sql = "INSERT INTO ".$tb_name."(".$str_fields.") VALUES (".$str_values.")";
			// echo "$sql";	
			$conn->exec($sql);// exec tanpa pengembalian
				
		} catch (Exception $e) {
			echo $sql."<br>".$e.getMessage();		
		}
	}

	// update_data_with_several_field_and_params
	function update_data($tb_name,$fields,$values_fields,$params,$values_params){

		try {
			if($GLOBALS['conn']==null){
				$GLOBALS['conn'] = pdo_connect();
			}
			$conn=$GLOBALS['conn'];
						
			// Params ---> nrp = :nrp				
	 		$str_params= convert_params_to_str($params);
			$str_fields = convert_params_to_str($fields); //format sama 

			$sql = "UPDATE ".$tb_name." SET ".$str_fields." WHERE ".$str_params;
			//echo "$sql";	
			$prepare_query = $conn->prepare($sql);
			
			//binding fields
			for($i=0;$i<count($fields);$i++){
				$prepare_query->bindValue(":".$fields[$i],$values_fields[$i]);
			}
			//binding params
			for($i=0;$i<count($params);$i++){
				$prepare_query->bindValue(":".$params[$i],$values_params[$i]);
			}
			
			$prepare_query->execute();
			// echo($sql);
				
		} catch (Exception $e) {
			echo $sql."<br>".$e.getMessage();		
		}

	}
	

	/*
		Fungsi dibawah ini digunakan untuk DELETE data yang fleksibel	
	*/
	// delete_data_with_several_params
	function delete_data($conn,$tb_name,$params,$values){

		try {
			if($GLOBALS['conn']==null){
				$GLOBALS['conn'] = pdo_connect();
			}
			$conn=$GLOBALS['conn'];
						
			// Params ---> nrp = :nrp				

	 		$str_params= convert_params_to_str($params);
			 

			$sql = "DELETE FROM ".$tb_name." WHERE ".$str_params;
			// echo "$sql";	
			$prepare_query = $conn->prepare($sql);
			//binding
			for($i=0;$i<count($params);$i++){
				$prepare_query->bindValue(":".$params[$i],$values[$i]);
			}
			
			$prepare_query->execute();
				
		} catch (Exception $e) {
			echo $sql."<br>".$e.getMessage();		
		}
	}
	



	/*
		fungsi ini digunakan untuk merubah array of field menjadi string (kode,nama, dsb)
	*/
	function convert_field_to_str($fields){
		$str ="";
		$banyak =count($fields);
		switch ($banyak) {
			//kalau seluruh field
			case 0:
				$str= '*';
				break;
			
			case 1:
				$str = $fields[0];
				break;
				//Kalau banyak field
			default :
				$str = $fields[0];
				for($i=1;$i<$banyak;$i++){
					$str = $str.",".$fields[$i];
				}
				break;

		}
		// kembalikan nilai str
		return $str;
	}

	/*
		fungsi ini digunakan untuk merubah array of field menjadi string (kode,nama, dsb)
	*/
	function convert_values_to_str($values){
		$str ="";
		// var_dump($values);
		$banyak =count($values);
		
		switch ($banyak) {
			
			case 1:
				$str = $values[0]===1?$values[0]:"'".$values[0]."'";

				break;
				//Kalau banyak values
			default :
				$str = (gettype($values[0])==gettype(1))?$values[0]:("'".$values[0]."'");
				// echo "$str";
				for($i=1;$i<$banyak;$i++){
					$str = $str.",".((gettype($values[$i])==gettype(1))?$values[$i]:"'".$values[$i]."'");
				}
				// echo "$str";
				break;

		}
		// kembalikan nilai str
		return $str;
	}
	/*
	
	/*
		fungsi ini digunakan untuk merubah array of params menjadi string (kode,nama, dsb)
	*/
	function convert_params_to_str($params){
		$str ="";
		$banyak =count($params);
		switch ($banyak) {
			//tidak mungkin params kosong menggunakan fungsi ini
			case 1:
				$str = $params[0]."=:".$params[0];
				break;
				//Kalau banyak field
			default :
				$str = $params[0]."=:".$params[0];
				for($i=1;$i<$banyak;$i++){
					$str = $str.", ".$params[$i]."=:".$params[$i];
				}
				break;

		}
		// kembalikan nilai str
		return $str;
	}

	
	// echo convert_params_to_str(array("test","2"));
	function select_extra($tb_name,$fields,$params,$values,$add){
		try{
			if($GLOBALS['conn']==null){
				$GLOBALS['conn'] = pdo_connect();
			}
			$conn=$GLOBALS['conn'];
			//jadikan field dalam bentuk string
			$str_fields= convert_field_to_str($fields);
			if(count($params)==0){
				$sql = "SELECT ".$str_fields." FROM ".$tb_name." WHERE ".$add;
				// echo "$sql";
				$prepare_query = $conn->prepare($sql);
				$prepare_query->execute();

			}else{
				$str_params = convert_params_to_str($params);
				$sql = "SELECT ".$str_fields." FROM ".$tb_name." WHERE ".$str_params." AND ".$add;
				
				$prepare_query = $conn->prepare($sql);
				//Binding
				for($i=0;$i<count($params);$i++){
					$prepare_query->bindValue(":".$params[$i],$values[$i]);	
				}
				$prepare_query->execute();
				
			}
			// echo "$sql";
			$hasil = $prepare_query->fetchAll();
			// var_dump($hasil);
		} catch (Exception $e) {
			echo $sql."<br>".$e.getMessage();		
		}
		return $hasil;
	}
	function query_biasa($sql){
		try {
			// echo $sql;
			if($GLOBALS['conn']==null){
				$GLOBALS['conn'] = pdo_connect();
			}

			$conn=$GLOBALS['conn'];
			$prepare_query = $conn->prepare($sql);
			$prepare_query->execute();
			$hasil = $prepare_query->fetchAll();		
			// print_r($hasil);

		} catch (Exception $e) {
			echo $sql."<br>".$e.getMessage();					
		}	
		return $hasil;	
	}
	// query_biasa("Select * from tb_user");
?>
