#include "LVS_Mysql.h"

//MYSQL *g_pstMySQLData = NULL;


unsigned long connectDb(MYSQL **ppmysqlData)
{
    //必备的一个数据结构  
    MYSQL *mysqlData = NULL;
    if(NULL == mysqlData)
    {
        mysqlData = new MYSQL();  
    }

    //初始化数据库  
    if (0 == mysql_library_init(0, NULL, NULL)) 
    {  
        printString("mysql_library_init() succeed",LVS_COLOR_WHITE,0);  
    } 
    else 
    {  
        printString("mysql_library_init() failed",LVS_COLOR_WHITE,0);
        return -1;  
    }  


    //初始化数据结构  
    if (NULL != mysql_init(mysqlData)) 
    {  
        printString("mysql_init() succeed",LVS_COLOR_WHITE,0);
    } 
    else 
    {  
        printString("mysql_init() failed",LVS_COLOR_WHITE,0);
        return -1;  
    }  


    //在连接数据库之前，设置额外的连接选项  
    //可以设置的选项很多，这里设置字符集，否则无法处理中文  
    if (0 == mysql_options(mysqlData, MYSQL_SET_CHARSET_NAME, "utf8")) 
    {  
        printString("mysql_options() succeed",LVS_COLOR_WHITE,0);
    } 
    else 
    {  
        printString( "mysql_options() failed" ,LVS_COLOR_WHITE,0);  
        return -1;  
    }     

    //连接数据库  
    if (NULL != mysql_real_connect(mysqlData, "localhost", "root", "123", "lvs",  
     3306, NULL, 0))  
    //这里的地址，用户名，密码，端口可以根据自己本地的情况更改  
    {  
        printString("mysql_real_connect() succeed",LVS_COLOR_WHITE,0);
    } 
    else 
    {  
        printString("mysql_real_connect() failed",LVS_COLOR_WHITE,0);
        return -1;  
    }  
	*ppmysqlData = mysqlData;
    return LVS_OK;
}

LVS_UINT32 closeConnectDb(MYSQL *mysqlData)
{
    /*断开连接并释放内存*/
    if(LVS_NULL_PTR != mysqlData)
    {
    	mysql_close(mysqlData);  
    	mysql_server_end();
        delete mysqlData;
        mysqlData = LVS_NULL_PTR;
    }
    return LVS_OK;
}
#if 0
unsigned long connectDb()
{
    //必备的一个数据结构  
    if(NULL == g_pstMySQLData)
    {
        g_pstMySQLData = new MYSQL();  
    }

    //初始化数据库  
    if (0 == mysql_library_init(0, NULL, NULL)) {  
    printString("mysql_library_init() succeed",LVS_COLOR_WHITE,0);  
    } else {  
    printString("mysql_library_init() failed",LVS_COLOR_WHITE,0);
    return -1;  
    }  


    //初始化数据结构  
    if (NULL != mysql_init(g_pstMySQLData)) {  
    printString("mysql_init() succeed",LVS_COLOR_WHITE,0);
    } else {  
    printString("mysql_init() failed",LVS_COLOR_WHITE,0);
    return -1;  
    }  


    //在连接数据库之前，设置额外的连接选项  
    //可以设置的选项很多，这里设置字符集，否则无法处理中文  
    if (0 == mysql_options(g_pstMySQLData, MYSQL_SET_CHARSET_NAME, "utf8")) {  
    printString("mysql_options() succeed",LVS_COLOR_WHITE,0);
    } else {  
    printString( "mysql_options() failed" ,LVS_COLOR_WHITE,0);  
    return -1;  
    }     

    //连接数据库  
    if (NULL != mysql_real_connect(g_pstMySQLData, "localhost", "root", "123", "lvs",  
     3306, NULL, 0))  
    //这里的地址，用户名，密码，端口可以根据自己本地的情况更改  
    {  
    printString("mysql_real_connect() succeed",LVS_COLOR_WHITE,0);
    } else {  
    printString("mysql_real_connect() failed",LVS_COLOR_WHITE,0);
    return -1;  
    }  

    return 0;
}
#endif

LVS_UINT32 insertTaskList(CC_CALLER_INFO_STRU *pCallerInfo)
{
	if(LVS_NULL_PTR == pCallerInfo)
    {
    	return -1;
	}
    unsigned long ulRet = 0;
    //连接数据库
#if 0
    if(NULL == g_pstMySQLData)
    {
        ulRet = connectDb();
        if(0 != ulRet)
        {
            /*打印错误信息*/
            printString("Connect database error!!!!!!!!!",LVS_COLOR_LIGHTRED, 0);
            return ulRet;
        }
    }
#endif
	MYSQL *mysqlData = NULL;
	connectDb(&mysqlData);
	
    //sql字符串  
    string sqlstr;    
    
    //向表中插入数据 
    sqlstr =  "INSERT INTO task_list(phone_num,tel_channel_id) VALUES(";
    sqlstr.append((char*)pCallerInfo->phoneNumber);
	sqlstr.append(",");
	sqlstr.append(changeLongToString((long) pCallerInfo->telChannelId));
    sqlstr.append(");");  

    if (0 == mysql_query(mysqlData, sqlstr.c_str())) {  
        printString( "mysql_query() insert data succeed" ,LVS_COLOR_WHITE,0);  
    } else {  
        printString( "mysql_query() insert data failed" ,LVS_COLOR_LIGHTRED,0);  
        return -1;  
    }

	closeConnectDb(mysqlData);
	mysqlData = LVS_NULL_PTR;
    return LVS_OK;
}

LVS_UINT32 insertTaskListReserve(CC_TASK_DISPATCH_INFO_STRU *pTaskDispatchInfo)
{
	if(LVS_NULL_PTR == pTaskDispatchInfo)
    {
    	return -1;
	}

    unsigned long ulRet = 0;
    /*连接数据库*/

	MYSQL *mysqlData = NULL;
	ulRet = connectDb(&mysqlData);
    if(LVS_OK != ulRet)
    {
        printString("insertTaskListReserve->connectDb failed",LVS_COLOR_LIGHTRED,LVS_FALSE);
        if(LVS_NULL_PTR != mysqlData)
        {
            delete mysqlData;
            mysqlData = LVS_NULL_PTR;
        }
        return LVS_ERR;
    }

    /*sql字符串*/
    string sqlstr;   
    /*向表中插入数据*/

    if(0 != pTaskDispatchInfo->taskId)  /*电话预约，则更新任务记录*/
    {
        sqlstr =  "UPDATE task_list SET dispatcher_id = ";
		sqlstr.append(changeLongToString((long)pTaskDispatchInfo->dispatcherId));
		sqlstr.append(",task_status = ");
		sqlstr.append(changeLongToString((long)2));
		sqlstr.append(",is_reserve = ");
		sqlstr.append(changeLongToString((long)1));
		sqlstr.append(",staff_num = '");
		sqlstr.append(pTaskDispatchInfo->userNumber);
		sqlstr.append("' where task_list_id = ");
        sqlstr.append(changeLongToString((long)pTaskDispatchInfo->taskId));
        sqlstr.append(";");
		
		if (0 == mysql_query(mysqlData, sqlstr.c_str())) 
        {   
			printString( "mysql_query() insert data succeed" ,LVS_COLOR_WHITE,0);  
		} 
        else 
        {  
			printString( "mysql_query() insert data failed" ,LVS_COLOR_LIGHTRED,0); 
			goto ERROR_PROC;
		}

    }
    else       /*手工预约，则插入任务记录，并取得插入的任务记录的ID*/
    {
        sqlstr =  "INSERT INTO task_list(phone_num,dispatcher_id,staff_num,task_status,channel_id,is_reserve) VALUES(";
		sqlstr.append(pTaskDispatchInfo->callerPhoneNumber);
		sqlstr.append(",");
		sqlstr.append(changeLongToString((long)pTaskDispatchInfo->dispatcherId));
		sqlstr.append(",'");
		sqlstr.append(pTaskDispatchInfo->userNumber);
		sqlstr.append("',2,1,1);");

	    if (0 == mysql_query(mysqlData, sqlstr.c_str())) 
        {  
	        printString( "mysql_query() insert data succeed" ,LVS_COLOR_WHITE,0);  
	    } 
        else 
        {  
	        printString( "mysql_query() insert data failed" ,LVS_COLOR_LIGHTRED,0);
			goto ERROR_PROC;
	    }

	    sqlstr = "SELECT LAST_INSERT_ID();";

	    MYSQL_RES *result = NULL;  
	    if( 0 == mysql_query(mysqlData, sqlstr.c_str())) {  
	        printString( "mysql_query() SELECT LAST_INSERT_ID() in insertTaskListReserve succeed" ,LVS_COLOR_WHITE,0);     

	        //一次性取得数据集  
	        result = mysql_store_result(mysqlData);  
	        MYSQL_ROW row = NULL;
	        row = mysql_fetch_row(result);  
	        /*取taskId*/
            if(LVS_NULL_PTR != row[0])
            {
	            pTaskDispatchInfo->taskId = parseStringToInt(row[0]);
            }
            mysql_free_result(result);
	    }
	    else {
	        printString( "mysql_query() SELECT LAST_INSERT_ID() in insertTaskListReserve failed" ,LVS_COLOR_LIGHTRED,0);
			//mysql_free_result(result);  
	        goto ERROR_PROC;
	    }		
		

    }
    
	closeConnectDb(mysqlData);
	mysqlData = LVS_NULL_PTR;
    return LVS_OK;

ERROR_PROC:
	closeConnectDb(mysqlData);
	mysqlData = LVS_NULL_PTR;
    return -1;    
}

LVS_UINT32 insertCallerInfo(CC_CALLER_INFO_STRU *pCallerInfo)
{
	if(LVS_NULL_PTR == pCallerInfo)
    {
    	return -1;
	}

#if 0
    unsigned long ulRet = 0;
    //连接数据库
    if(NULL == g_pstMySQLData)
    {
        ulRet = connectDb();
        if(0 != ulRet)
        {
            /*打印错误信息*/
            printString("Connect database error!!!!!!!!!",LVS_COLOR_LIGHTRED, 0);
            return ulRet;
        }
    }
#endif

	MYSQL *mysqlData = NULL;
	connectDb(&mysqlData);
    
    //sql字符串  
    string sqlstr;    
    
    //向表中插入数据 
    sqlstr =  "INSERT INTO caller_info (phone_num,name,department) VALUES(";
    sqlstr.append((char*)pCallerInfo->phoneNumber);
    sqlstr.append(",'");
    sqlstr.append((char*)pCallerInfo->name);
    sqlstr.append("','");
    sqlstr.append((char*)pCallerInfo->department);
    sqlstr.append("');");  

    if (0 == mysql_query(mysqlData, sqlstr.c_str())) {  
        printString( "mysql_query() insert data succeed" ,LVS_COLOR_WHITE,0);  
    } else {  
        printString( "mysql_query() insert data failed" ,LVS_COLOR_LIGHTRED,0);  
        return -1;  
    }
	closeConnectDb(mysqlData);
	mysqlData = LVS_NULL_PTR;
    return LVS_OK;
}

LVS_UINT32 insertStaffInfo(CC_STAFF_INFO_STRU *pStaffInfo)
{
	if(LVS_NULL_PTR == pStaffInfo)
    {
    	return -1;
	}

    unsigned long ulRet = 0;
    //连接数据库
	MYSQL *mysqlData = NULL;
	connectDb(&mysqlData);

    
    //sql字符串  
    string sqlstr;    
    
    //向表中插入数据 
    sqlstr =  "INSERT INTO caller_info (name,name_spell,post,callNumber,phoneNumber) VALUES('";
    sqlstr.append((char*)pStaffInfo->name);
    sqlstr.append("','");
    sqlstr.append((char*)pStaffInfo->nameSpell);
    sqlstr.append("','");
    sqlstr.append((char*)pStaffInfo->post);
    sqlstr.append("',");
    sqlstr.append((char*)pStaffInfo->callNumber);
    sqlstr.append(",");
    sqlstr.append((char*)pStaffInfo->phoneNumber);
    sqlstr.append(");");

    if (0 == mysql_query(mysqlData, sqlstr.c_str())) 
	{  
        printString( "mysql_query() insert data succeed" ,LVS_COLOR_WHITE,0);  
    } 
	else 
	{  
        printString( "mysql_query() insert data failed" ,LVS_COLOR_LIGHTRED,0);  
		closeConnectDb(mysqlData);
		mysqlData = LVS_NULL_PTR;
        return -1;  
    }
	
	closeConnectDb(mysqlData);
	mysqlData = LVS_NULL_PTR;
    return LVS_OK;
}


LVS_UINT32 insertTaskType(CC_TASK_INFO_STRU *pTaskInfo)
{
	if(LVS_NULL_PTR == pTaskInfo)
    {
    	return -1;
	}

    unsigned long ulRet = 0;
    //连接数据库
	MYSQL *mysqlData = NULL;
	connectDb(&mysqlData);

    //sql字符串  
    string sqlstr;    
    
    //向表中插入数据 
    sqlstr =  "INSERT INTO task_info (task_id,task_name,task_type) VALUES(";
    sqlstr.append(changeLongToString((long)pTaskInfo->taskId));
    sqlstr.append(",'");
    sqlstr.append((char*)pTaskInfo->taskName);
    sqlstr.append("',");
    sqlstr.append(changeLongToString((long)pTaskInfo->taskType));
    sqlstr.append(");");  

    if (0 == mysql_query(mysqlData, sqlstr.c_str())) {  
        printString( "mysql_query() insert data succeed" ,LVS_COLOR_WHITE,0);  
    } else {  
        printString( "mysql_query() insert data failed!!!!!!!" ,LVS_COLOR_LIGHTRED,0);  
		closeConnectDb(mysqlData);
		mysqlData = LVS_NULL_PTR;
        return -1;  
    }
	
	closeConnectDb(mysqlData);
	mysqlData = LVS_NULL_PTR;
    return LVS_OK;
}


LVS_UINT32 insertTaskDtl(CC_TASK_DISPATCH_INFO_STRU *pTaskDispatchInfo)
{
	if(LVS_NULL_PTR == pTaskDispatchInfo)
    {
    	return -1;
	}

    unsigned long ulRet = 0;
    //连接数据库
	MYSQL *mysqlData = NULL;
	ulRet = connectDb(&mysqlData);

    if(LVS_OK != ulRet)
    {
        printString("insertTaskDtl->connectDb failed",LVS_COLOR_LIGHTRED,LVS_FALSE);
        if(LVS_NULL_PTR != mysqlData)
        {
            delete mysqlData;
            mysqlData = LVS_NULL_PTR;
        }
        return LVS_ERR;
    }

       
    string sqlstr;    /*sql字符串*/     
    
    //LVS_UINT32 taskLength = pTaskDispatchInfo->taskType;
    //向表中插入数据 
    LVS_UINT32 lengthOfTaskTypeSet = sizeof(pTaskDispatchInfo->taskType)/sizeof( pTaskDispatchInfo->taskType[0]);
    for(LVS_UINT32 i = 0; i < lengthOfTaskTypeSet; i++)
    {
        if(0 == pTaskDispatchInfo->taskType[i]) 
        {
            continue;
        }
        sqlstr =  "INSERT INTO task_dtl (task_list_id,task_id) VALUES(";
        sqlstr.append(changeLongToString((long)pTaskDispatchInfo->taskId));
        sqlstr.append(",");
        sqlstr.append(changeLongToString((long)pTaskDispatchInfo->taskType[i]));
        sqlstr.append(");");  
    
        if (0 == mysql_query(mysqlData, sqlstr.c_str())) 
        {  
            printString( "mysql_query() insertTaskDtl succeed" ,LVS_COLOR_WHITE,0);  
        } 
        else 
        {  
            printString( "mysql_query() insertTaskDtl failed!!!!!!!!!!!" ,LVS_COLOR_LIGHTRED,0);
			closeConnectDb(mysqlData);
			mysqlData = LVS_NULL_PTR;
            return -1;  
        }

    }

	closeConnectDb(mysqlData);
	mysqlData = LVS_NULL_PTR;
	return LVS_OK;
}

LVS_UINT32 insertReserveList(CC_TASK_DISPATCH_INFO_STRU *pTaskDispatchInfo)
{
	if(LVS_NULL_PTR == pTaskDispatchInfo)
    {
    	return -1;
	}

    unsigned long ulRet = 0;
    //连接数据库
	MYSQL *mysqlData = NULL;
	ulRet = connectDb(&mysqlData);

    if(LVS_OK != ulRet)
    {
        printString("insertReserveList->connectDb failed",LVS_COLOR_LIGHTRED,LVS_FALSE);
        if(LVS_NULL_PTR != mysqlData)
        {
            delete mysqlData;
            mysqlData = LVS_NULL_PTR;
        }
        return LVS_ERR;
    }

    string sqlstr;    /*sql字符串*/     
    //向表中插入数据 
    sqlstr =  "INSERT INTO reserve_list (task_list_id, reserve_time, reserve_status, reserve_department, reserve_phone_num) VALUES(";
    sqlstr.append(changeLongToString((long)pTaskDispatchInfo->taskId));
    sqlstr.append(",'");
    sqlstr.append((char*)pTaskDispatchInfo->datetime);
    sqlstr.append("',0,'"); /*reserve_status: 0-预约未处理；1-预约已发出，但还未处理；2-预约已处理。*/
    sqlstr.append((char*)pTaskDispatchInfo->department);
    sqlstr.append("',");
    sqlstr.append((char*)pTaskDispatchInfo->callerPhoneNumber);
    sqlstr.append(");");

    if (0 == mysql_query(mysqlData, sqlstr.c_str())) 
    {  
        printString( "mysql_query() insertReserveList succeed" ,LVS_COLOR_WHITE,0);  
    } 
    else 
    {  
        printString( "mysql_query() insertReserveList failed!!!!!!!" ,LVS_COLOR_LIGHTRED,0);
		closeConnectDb(mysqlData);
		mysqlData = LVS_NULL_PTR;
        return -1;  
    }

	closeConnectDb(mysqlData);
	mysqlData = LVS_NULL_PTR;
    return LVS_OK;
}

LVS_UINT32 insertReserveTaskDtl(CC_TASK_DISPATCH_INFO_STRU *pTaskDispatchInfo)
{
	if(LVS_NULL_PTR == pTaskDispatchInfo)
    {
    	return -1;
	}

    unsigned long ulRet = 0;
    //连接数据库
	MYSQL *mysqlData = NULL;
	connectDb(&mysqlData);
       
    string sqlstr;    /*sql字符串*/     
    
    //LVS_UINT32 taskLength = pTaskDispatchInfo->taskType;
    //向表中插入数据 
    for(int i = 0; i < sizeof(pTaskDispatchInfo->taskType)/sizeof( pTaskDispatchInfo->taskType[0]); i++)
    {
        if(0xffff == pTaskDispatchInfo->taskType[i]) 
        {
            break;
        }
        sqlstr =  "INSERT INTO reserve_task_dtl (task_list_id,task_id) VALUES(";
        sqlstr.append((char*)pTaskDispatchInfo->taskId);
        sqlstr.append(",");
        sqlstr.append((char*)pTaskDispatchInfo->taskType[i]);
        sqlstr.append(");");  
    
        if (0 == mysql_query(mysqlData, sqlstr.c_str())) {  
            printString( "mysql_query() insertReserveTaskDtl succeed" ,LVS_COLOR_WHITE,0);  
        } else {  
            printString( "mysql_query() insertReserveTaskDtl failed!!!!!!!!!!!" ,LVS_COLOR_LIGHTRED,0);  
			closeConnectDb(mysqlData);
            return -1;  
        }

    }
	closeConnectDb(mysqlData);
    return LVS_OK;
    
}

LVS_UINT32 queryCallerInfo(CC_CALLER_INFO_STRU *pCallerInfo)
{
	if(LVS_NULL_PTR == pCallerInfo)
    {
    	return -1;
	}

    unsigned long ulRet = 0;
    //连接数据库
	MYSQL *mysqlData = NULL;
	connectDb(&mysqlData);
    
    string sqlstr;    /*sql字符串*/
    sqlstr = "SELECT LAST_INSERT_ID();";
    LVS_UINT32 length = -1;

    MYSQL_RES *result = NULL;  
    if( 0 == mysql_query(mysqlData, sqlstr.c_str())) {  
        printString( "mysql_query() SELECT LAST_INSERT_ID() succeed" ,LVS_COLOR_WHITE,0);     

        //一次性取得数据集  
        result = mysql_store_result(mysqlData);  
        MYSQL_ROW row = NULL;
        row = mysql_fetch_row(result);  
        /*取taskId*/
		if(LVS_NULL_PTR == row[0]){}
		else
		{
        	pCallerInfo->taskId = parseStringToInt(row[0]);
		}
    }
    else {
        printString( "mysql_query() SELECT LAST_INSERT_ID() failed" ,LVS_COLOR_LIGHTRED,0);  
        goto ERROR_PROC;
    }  
    
    sqlstr = "SELECT department, name FROM caller_info where phone_num = ";
    sqlstr.append((char*)pCallerInfo->phoneNumber);
    sqlstr.append(";");
    
    if (0 == mysql_query(mysqlData, sqlstr.c_str())) {  
        printString( "mysql_query() select data succeed" ,LVS_COLOR_WHITE,0);     

        //一次性取得数据集
        mysql_free_result(result);
        result = mysql_store_result(mysqlData);  

        MYSQL_ROW row = NULL;
        row = mysql_fetch_row(result);  
        LVS_UINT32 rowcount = (LVS_UINT32)mysql_num_rows(result);
        
        /*查不到*/
        if(0 == rowcount) 
        {
            printString("This phoneNumber is not exist in db!!", LVS_COLOR_LIGHTRED, 0);
            goto ERROR_PROC;
        }
        //pCallerInfo->department = row[0];
		if(LVS_NULL_PTR == row[0]){}
		else
		{
			if(strlen(row[0]) > sizeof(pCallerInfo->department))
			{
				length = sizeof(pCallerInfo->department);
			}
			else
			{
				length = strlen(row[0]);
			}
			memcpy(pCallerInfo->department, row[0], length);
		}
		/*查询姓名*/
		if(LVS_NULL_PTR == row[1]){}
		else
		{
	        if(strlen(row[1]) > sizeof(pCallerInfo->name))
			{
				length = sizeof(pCallerInfo->name);
			}
			else
			{
				length = strlen(row[1]);
			}
			memcpy(pCallerInfo->name, row[1], length);
		}        
    } 
    else {
        printString( "mysql_query() select data failed" ,LVS_COLOR_LIGHTRED,0);  
        goto ERROR_PROC;
        //mysql_free_result(result);
        //return -1;  
    }  

	mysql_free_result(result);
	closeConnectDb(mysqlData);
	mysqlData = LVS_NULL_PTR;
    return LVS_OK;

ERROR_PROC:
    mysql_free_result(result);
	closeConnectDb(mysqlData);
	mysqlData = LVS_NULL_PTR;
    return -1;
}

//LVS_INT32 queryStaffInfoUseNameSpell(CC_QUERY_STAFF_KEY_INFO_STRU *pQueryStaffInfo, CC_STAFF_INFO_SET_STRU *pstStaffInfoSet)
LVS_UINT32 queryStaffInfoUseNameSpell(LVS_MSG_INFO_STRU *pMsg)
{
	if(LVS_NULL_PTR == pMsg)
    {
    	return -1;
	}

    unsigned long ulRet = 0;
    //连接数据库
	MYSQL *mysqlData = NULL;
	connectDb(&mysqlData);
    

    CC_QUERY_STAFF_KEY_INFO_STRU *pQueryStaffInfo = (CC_QUERY_STAFF_KEY_INFO_STRU*) pMsg->pMsgData;
    CC_STAFF_INFO_SET_STRU *pstStaffInfoSet;
    
    pMsg->pMsgData = NULL;
    
    //sql字符串  
    string sqlstr;    
    LVS_UINT32 length = -1;
    
    sqlstr = "SELECT staff_num,staff_name,staff_post,staff_status,staff_call_num FROM staff_info where staff_name_spell like '";
    sqlstr.append((char*)pQueryStaffInfo->nameSpell);
    sqlstr.append("%';");

    MYSQL_RES *result = NULL;  
    if (0 == mysql_query(mysqlData, sqlstr.c_str())) {  
        printString( "mysql_query() select data FROM staff_info succeed" ,LVS_COLOR_WHITE,0);     

        //一次性取得数据集  
        result = mysql_store_result(mysqlData);  
        LVS_UINT32 fieldcount = mysql_num_fields(result);  
        LVS_UINT32 rowcount = (LVS_UINT32)mysql_num_rows(result);

        //CC_STAFF_INFO_SET_STRU staff_info_set[rowcount];
        /*查不到*/
        if(0 == rowcount)
        {
            printString("This StaffInfo is not exist in db!!", LVS_COLOR_LIGHTRED, 0);
            goto ERROR_PROC;
        }
        
        pstStaffInfoSet = (CC_STAFF_INFO_SET_STRU*)malloc(rowcount * sizeof(CC_STAFF_INFO_STRU));

        if(LVS_NULL_PTR == pstStaffInfoSet)
        {
            goto ERROR_PROC;
        }        
        memset(pstStaffInfoSet, 0 ,rowcount * sizeof(CC_STAFF_INFO_STRU));

        CC_STAFF_INFO_STRU *pstStaffInfo = LVS_NULL_PTR;
        MYSQL_ROW row = NULL;
        for(LVS_UINT32 i = 0; i < rowcount; i++)
        {
            row = mysql_fetch_row(result);            
            pstStaffInfo = (CC_STAFF_INFO_STRU*)(pstStaffInfoSet->stStaffInfoList) + i;
            //取员工工号
			if(LVS_NULL_PTR == row[0]){}
			else
			{
	            if(strlen(row[0]) > sizeof(pstStaffInfo->userNumber))
	            {
	                length = sizeof(pstStaffInfo->userNumber);
	            }
	            else
	            {
	                length = strlen(row[0]);
	            }            
	            memcpy(pstStaffInfo->userNumber,row[0],length);
			}
            /*取员工姓名*/
			if(LVS_NULL_PTR == row[1]){}
			else
			{
	            if(strlen(row[1]) > sizeof(pstStaffInfo->name))
	            {
	                length = sizeof(pstStaffInfo->name);
	            }
	            else
	            {
	                length = strlen(row[1]);
	            }            
	            memcpy(pstStaffInfo->name,row[1],length);      
			}
            /*取员工岗位*/
			if(LVS_NULL_PTR == row[2]){}
			else
			{
	            if(strlen(row[2]) > sizeof(pstStaffInfo->post))
	            {
	                length = sizeof(pstStaffInfo->post);
	            }
	            else
	            {
	                length = strlen(row[2]);
	            }            
	            memcpy(pstStaffInfo->post,row[2],length);  
			}
            /*取员工状态*/
			if(LVS_NULL_PTR == row[3]){}
			else
			{
            	pstStaffInfo->state = parseStringToInt(row[3]);
			}
            /*取员工呼机号*/
			if(LVS_NULL_PTR == row[4]){}
			else
			{
	            if(strlen(row[4]) > sizeof(pstStaffInfo->callNumber))
	            {
	                length = sizeof(pstStaffInfo->callNumber);
	            }
	            else
	            {
	                length = strlen(row[4]);
	            }            
	            memcpy(pstStaffInfo->callNumber,row[4],length);              
			}                        
        }
        pMsg->pMsgData = (LVS_VOID*)pstStaffInfoSet;
        pMsg->ulMsgLen = rowcount * sizeof(CC_STAFF_INFO_STRU);
        /**rq 2012年6月11日0:34:50 ***/
    } 
    else {
        printString( "mysql_query() select data FROM staff_info failed" ,LVS_COLOR_LIGHTRED,0);  
        goto ERROR_PROC;
    }  
    mysql_free_result(result);
	closeConnectDb(mysqlData);
	mysqlData = LVS_NULL_PTR;
    return LVS_OK;

ERROR_PROC:
    mysql_free_result(result);
	closeConnectDb(mysqlData);
	mysqlData = LVS_NULL_PTR;
    return -1;
}

LVS_UINT32 quaryTaskListBetweenStartAndEnd(LVS_MSG_INFO_STRU *pMsg)
{
	if(LVS_NULL_PTR == pMsg)
    {
    	return -1;
	}

    unsigned long ulRet = 0;
    //连接数据库
	MYSQL *mysqlData = NULL;
	connectDb(&mysqlData);

    CC_VIEW_TASK_LIST_BETWEEN_START_END *pViewTaskListBetweenSAndE = (CC_VIEW_TASK_LIST_BETWEEN_START_END*) pMsg->pMsgData;
	CC_VIEW_TASK_LIST_STRU *pViewTaskList;
    CC_VIEW_TASK_LIST_SET_STRU *pViewTaskListSet;

    pMsg->pMsgData = NULL;

    //sql字符串  
    string sqlstr;    
    LVS_UINT32 length = -1;
    
	sqlstr = "Select task_list.task_list_id, task_list.task_happen_time, caller_info.department, task_list.phone_num, staff_info.staff_name, task_list.task_status,\
				dispatcher_info.dispatcher_name, task_list.is_reserve from task_list\
				left join caller_info on task_list.phone_num = caller_info.phone_num\
				left join staff_info on task_list.staff_num = staff_info.staff_num\
				left join dispatcher_info on task_list.dispatcher_id = dispatcher_info.dispatcher_id\
				where date(task_list.task_happen_time) between '";
	sqlstr.append((char*)pViewTaskListBetweenSAndE->startDate);
	sqlstr.append("' and '");
    sqlstr.append((char*)pViewTaskListBetweenSAndE->endDate);
	sqlstr.append("';");

	MYSQL_RES *result = NULL;  
    if (0 == mysql_query(mysqlData, sqlstr.c_str())) {  
        printString( "mysql_query() quaryTaskListBetweenStartAndEnd succeed" ,LVS_COLOR_WHITE,0);     

        //一次性取得数据集  
        result = mysql_store_result(mysqlData);  
        LVS_UINT32 fieldcount = mysql_num_fields(result);  
        LVS_UINT32 rowcount = (LVS_UINT32)mysql_num_rows(result);

        //CC_STAFF_INFO_SET_STRU staff_info_set[rowcount];
        /*查不到*/
        if(0 == rowcount)
        {
            printString("quaryTaskListBetweenStartAndEnd not have a row in db!!", LVS_COLOR_LIGHTRED, 0);
            goto ERROR_PROC;
        }
        
        pViewTaskListSet = (CC_VIEW_TASK_LIST_SET_STRU*)malloc(rowcount * sizeof(CC_VIEW_TASK_LIST_STRU));

        if(LVS_NULL_PTR == pViewTaskListSet)
        {
            goto ERROR_PROC;
        }        
        memset(pViewTaskListSet, 0 ,rowcount * sizeof(CC_VIEW_TASK_LIST_STRU));

        MYSQL_ROW row = NULL;
        for(LVS_UINT32 i = 0, taskListId = -1, isReserve = -1; i < rowcount; i++)
        {
            row = mysql_fetch_row(result);            
            pViewTaskList = (CC_VIEW_TASK_LIST_STRU*)(pViewTaskListSet->stViewTaskList) + i;
			
			/*取task_list_id*/
			if(LVS_NULL_PTR == row[0])
			{
				taskListId = -1;
			}
			else 
			{
				taskListId = changeStringToUlong(row[0]);
			}
            //取任务发生时间
			if(LVS_NULL_PTR == row[1]){}
			else
			{
	            if(strlen(row[1]) > sizeof(pViewTaskList->datetime))
	            {
	                length = sizeof(pViewTaskList->datetime);
	            }
	            else
	            {
	                length = strlen(row[1]);
	            }     
       		    memcpy(pViewTaskList->datetime,row[1],length);
			}
			
            /*取任务来源科室*/
			if(LVS_NULL_PTR == row[2]){}
			else
			{
		        if(strlen(row[2]) > sizeof(pViewTaskList->department))
		        {
		            length = sizeof(pViewTaskList->department);
		        }
		        else
		        {
		            length = strlen(row[2]);
		        }            
		        memcpy(pViewTaskList->department,row[2],length);
			}
            /*取任务来源电话号码*/
			if(LVS_NULL_PTR == row[3]){}
			else
			{
	            if(strlen(row[3]) > sizeof(pViewTaskList->callerPhoneNumber))
	            {
	                length = sizeof(pViewTaskList->callerPhoneNumber);
	            }
	            else
	            {
	                length = strlen(row[3]);
	            }            
	            memcpy(pViewTaskList->callerPhoneNumber,row[3],length);
			}
            /*取被派遣员工的姓名*/
			if(LVS_NULL_PTR == row[4]){}
			else
			{
		        if(strlen(row[4]) > sizeof(pViewTaskList->staffName))
		        {
		            length = sizeof(pViewTaskList->staffName);
		        }
		        else
		        {
		            length = strlen(row[4]);
		        }            
		        memcpy(pViewTaskList->staffName,row[4],length);
			}
            /*取任务派遣状态*/
			if(LVS_NULL_PTR == row[5]){}
			else
			{
				pViewTaskList->taskState = changeStringToUlong(row[5]);
			}
            /*取任务调度员姓名*/
			if(LVS_NULL_PTR == row[6]){}
			else
			{
		        if(strlen(row[6]) > sizeof(pViewTaskList->dispatcher_name))
		        {
		            length = sizeof(pViewTaskList->dispatcher_name);
		        }
		        else
		        {
		            length = strlen(row[6]);
		        }            
		        memcpy(pViewTaskList->dispatcher_name,row[6],length);
			}
			/*取是否预约*/
			if(LVS_NULL_PTR == row[7]){}
			else
			{
				isReserve = changeStringToUlong(row[7]);
			}
			/*取此次任务的任务类型列表，最多16种任务*/
			string sqlstrDtl;
			sqlstrDtl = "Select task_id from task_dtl where task_list_id = ";
			sqlstrDtl.append((char*)row[0]);
			sqlstrDtl.append(";");
			MYSQL_RES *resultDtl = NULL;  
			if (0 == mysql_query(mysqlData, sqlstrDtl.c_str())) {  
			    printString( "mysql_query() Select task_id from task_dtl succeed" ,LVS_COLOR_WHITE,0);
				//mysql_free_result(result);
		        resultDtl = mysql_store_result(mysqlData);  
				LVS_UINT32 fieldcountDtl = mysql_num_fields(resultDtl);  
				LVS_UINT32 rowcountDtl = (LVS_UINT32)mysql_num_rows(resultDtl);

				/*查不到*/
				if(0 == rowcountDtl)
				{
				    printString("Select task_id from task_dtl not have a row in db!!", LVS_COLOR_LIGHTRED, 0);
					mysql_free_result(resultDtl);
					//closeConnectDb(mysqlData);
					goto ERROR_PROC;
				}
				
				MYSQL_ROW rowDtl = NULL;
				for(LVS_UINT32 i = 0; i < rowcountDtl; i++)
				{
					rowDtl = mysql_fetch_row(resultDtl);
					pViewTaskList->taskType[i] = changeStringToUlong((char*)rowDtl[0]);
				}
				mysql_free_result(resultDtl);
			}
			
        }
		
        pMsg->pMsgData = (LVS_VOID*)pViewTaskListSet;
        pMsg->ulMsgLen = rowcount * sizeof(CC_VIEW_TASK_LIST_STRU);
    }
    else {
        printString( "mysql_query() quaryTaskListBetweenStartAndEnd failed" ,LVS_COLOR_LIGHTRED,0);  
        goto ERROR_PROC;
    }  
    mysql_free_result(result);
	closeConnectDb(mysqlData);
	mysqlData = LVS_NULL_PTR;
    return LVS_OK;
	
ERROR_PROC:
    mysql_free_result(result);
	closeConnectDb(mysqlData);
	mysqlData = LVS_NULL_PTR;
    return -1;    
}

LVS_UINT32 quaryAllTaskTypeList(LVS_MSG_INFO_STRU *pMsg)
{
	if(LVS_NULL_PTR == pMsg)
    {
    	return -1;
	}

	unsigned long ulRet = 0;
    //连接数据库
	MYSQL *mysqlData = NULL;
	connectDb(&mysqlData);


	CC_TASK_INFO_STRU *pTaskInfo;
    CC_TASK_INFO_SET_STRU *pTaskInfoSet;

    //sql字符串  
    string sqlstr;    
    LVS_UINT32 length = -1;
	sqlstr = "Select task_id,task_name,task_type from task_info;";

	
	MYSQL_RES *result = NULL;  
	if (0 == mysql_query(mysqlData, sqlstr.c_str())) {  
		printString( "mysql_query() Select * from task_info succeed" ,LVS_COLOR_WHITE,0);	  

		//一次性取得数据集	
		result = mysql_store_result(mysqlData);  
		LVS_UINT32 fieldcount = mysql_num_fields(result);  
		LVS_UINT32 rowcount = (LVS_UINT32)mysql_num_rows(result);

		/*查不到*/
		if(0 == rowcount)
		{
			printString("Select * from task_info, not have a row in db!!", LVS_COLOR_LIGHTRED, 0);
			goto ERROR_PROC;
		}
		
		pTaskInfoSet = (CC_TASK_INFO_SET_STRU*)malloc(rowcount * sizeof(CC_TASK_INFO_STRU));

		if(LVS_NULL_PTR == pTaskInfoSet)
		{
			goto ERROR_PROC;
		}		 
		memset(pTaskInfoSet, 0 ,rowcount * sizeof(CC_TASK_INFO_STRU));

		MYSQL_ROW row = NULL;
		for(LVS_UINT32 i = 0; i < rowcount; i++)
		{
			row = mysql_fetch_row(result);			  
			pTaskInfo = (CC_TASK_INFO_STRU*)(pTaskInfoSet->stTaskInfo) + i;
			
			/*取task_id*/
			if(LVS_NULL_PTR == row[0]){}
			else
			{
				pTaskInfo->taskId= changeStringToUlong(row[0]);
			}
			//取task_name
			if(LVS_NULL_PTR == row[1]){}
			else
			{
				if(strlen(row[1]) > sizeof(pTaskInfo->taskName))
				{
					length = sizeof(pTaskInfo->taskName);
				}
				else
				{
					length = strlen(row[1]);
				}			 
				memcpy(pTaskInfo->taskName,row[1],length);
			}
			/*取task_type*/
			if(LVS_NULL_PTR == row[2]){}
			else
			{
				pTaskInfo->taskType= changeStringToUlong(row[2]);
			}
		}

		pMsg->pMsgData = (LVS_VOID*)pTaskInfoSet;
        pMsg->ulMsgLen = rowcount * sizeof(CC_TASK_INFO_STRU);
    }
    else {
        printString( "mysql_query()  Select * from task_info failed" ,LVS_COLOR_LIGHTRED,0);  
        goto ERROR_PROC;
    }  
    mysql_free_result(result);
	closeConnectDb(mysqlData);
	mysqlData = LVS_NULL_PTR;
	return LVS_OK;
	
ERROR_PROC:
	mysql_free_result(result);
	closeConnectDb(mysqlData);
	mysqlData = LVS_NULL_PTR;
	return -1;
		
}

LVS_UINT32 updateTaskList(CC_TASK_DISPATCH_INFO_STRU *pTaskDispatchInfo)
{
	if(LVS_NULL_PTR == pTaskDispatchInfo)
    {
    	return -1;
	}

    unsigned long ulRet = 0;
    //连接数据库
	MYSQL *mysqlData = NULL;
	connectDb(&mysqlData);
    
    //sql字符串  
    string sqlstr;    
    //LVS_UINT32 length = -1;
    if(0 == pTaskDispatchInfo->isReserve) /*非预约消息*/
    {
        sqlstr = "update task_list set task_status = 1, dispatcher_id = ";
        sqlstr.append(changeLongToString((long) pTaskDispatchInfo->dispatcherId));
		sqlstr.append(", staff_num = '");
		sqlstr.append((char*)pTaskDispatchInfo->userNumber);
        sqlstr.append("' where task_list_id = ");
        sqlstr.append(changeLongToString((long)pTaskDispatchInfo->taskId));
        sqlstr.append(";");
 
        if (0 == mysql_query(mysqlData, sqlstr.c_str())) {  
            printString( "mysql_query() update task_list task_status succeed" ,LVS_COLOR_WHITE,0);    
        } 
        else {
            printString( "mysql_query() update task_list task_status failed!!!!" ,LVS_COLOR_LIGHTRED,0);  
			closeConnectDb(mysqlData);
			mysqlData = LVS_NULL_PTR;
            return -1;  
        }  
    }
    else if(1 == pTaskDispatchInfo->isReserve) /*预约消息*/
    {
        sqlstr = "update task_list set task_status = 3, isReserve = 1, dispatcher_id = ";
        sqlstr.append(changeLongToString((long) pTaskDispatchInfo->dispatcherId));
		sqlstr.append(", staff_num = '");
		sqlstr.append((char*) pTaskDispatchInfo->userNumber);
        sqlstr.append("' where task_list_id = ");
        sqlstr.append(changeLongToString((long)pTaskDispatchInfo->taskId));
        sqlstr.append(";");

        if (0 == mysql_query(mysqlData, sqlstr.c_str())) {  
            printString( "mysql_query() update task_list task_status succeed" ,LVS_COLOR_WHITE,0);    
        } 
        else {
            printString( "mysql_query() update task_list task_status failed!!!!" ,LVS_COLOR_LIGHTRED,0);  
			closeConnectDb(mysqlData);
			mysqlData = LVS_NULL_PTR;
            return -1;  
        }  
    }
    closeConnectDb(mysqlData);
	mysqlData = LVS_NULL_PTR;
    return LVS_OK;
}

LVS_UINT32 updateReserveList(CC_TASK_DISPATCH_INFO_STRU *pTaskDispatchInfo)
{
	if(LVS_NULL_PTR == pTaskDispatchInfo)
    {
    	return -1;
	}

    unsigned long ulRet = 0;
    //连接数据库
	MYSQL *mysqlData = NULL;
	connectDb(&mysqlData);
    
    //sql字符串  
    string sqlstr;    
    /*预约的时候预约者如果指定被派遣者记录在reserve_list表的staff_num字段里，但是实际被派遣的员工号记录在表task_list的字段staff_num里面。*/
	/*所以这里不更新被派遣者信息*/
	/*reserve_status: 0-预约未处理；1-预约已发出，但还未处理；2-预约已处理。*/
	sqlstr = "update reserve_list set reserve_status = 2 where task_list_id = ";
    sqlstr.append(changeLongToString((long)pTaskDispatchInfo->taskId));
    sqlstr.append(";");

    if (0 == mysql_query(mysqlData, sqlstr.c_str())) {  
        printString( "mysql_query() updateReserveList succeed" ,LVS_COLOR_WHITE,0);    
    } 
    else {
        printString( "mysql_query() updateReserveList failed!!!!" ,LVS_COLOR_LIGHTRED,0);
		closeConnectDb(mysqlData);
		mysqlData = LVS_NULL_PTR;
        return -1;  
    }  
    closeConnectDb(mysqlData);
	mysqlData = LVS_NULL_PTR;
    return LVS_OK;
}

LVS_INT32 getTheRecentReserveSeconds()
{
    unsigned long ulRet = 0;
    //连接数据库
	MYSQL *mysqlData = NULL;
	connectDb(&mysqlData);


	SYSTEMTIME systime; 
	GetLocalTime( &systime );

    LVS_UINT32 sysYear = systime.wYear;
    LVS_UINT32 sysMonth = systime.wMonth;
    LVS_UINT32 sysDay = systime.wDay;
    LVS_UINT32 sysHour = systime.wHour;
    LVS_UINT32 sysMinute = systime.wMinute;
    LVS_UINT32 sysSecond = systime.wSecond;
    LVS_UINT32 dateDiff = 0;

    //当前日期字符串  
    string sysDateStr = changeLongToString((long)sysYear);
    sysDateStr.append("-");
    sysDateStr.append(changeLongToString((long)sysMonth));
    sysDateStr.append("-");
    sysDateStr.append(changeLongToString((long)sysDay));    

 
    LVS_UINT32 reserveTimeToSec = 0;
    string     reserveDate  = "";
	string	   reserveDateTime ="";

	LVS_INT32 retTimeSec;
	string str;
        
    //sql字符串  
    string sqlstr;    
    //LVS_UINT32 length = -1;
    MYSQL_RES *result = NULL;      
    
    sqlstr = "Select date(reserve_time), TIME_TO_SEC(reserve_time), reserve_time from reserve_list where reserve_time = (select min(reserve_time) from reserve_list where reserve_status = 0);";
    
    if (0 == mysql_query(mysqlData, sqlstr.c_str())) {  
        printString( "Select date(reserve_time), TIME_TO_SEC(reserve_time) from reserve_list where reserve_time = (select min(reserve_time) from reserve_list) and reserve_status = 0; succeed" ,LVS_COLOR_WHITE,0);    

        //一次性取得数据集  
        result = mysql_store_result(mysqlData);  

        MYSQL_ROW row = NULL;
        row = mysql_fetch_row(result);  
        LVS_UINT32 rowcount = (LVS_UINT32)mysql_num_rows(result);
        
        /*查不到*/
        if(0 == rowcount) 
        {
            printString("查不到 Select date(reserve_time), TIME_TO_SEC(reserve_time) !!", LVS_COLOR_LIGHTRED, 0);
            goto ERROR_PROC;
        }
        else 
        {
            /*取日期*/
            reserveDate.append((char*)row[0]);
            /*取时间，以秒为单位*/
            reserveTimeToSec = changeStringToUlong(row[1]);
			/*取整个 日期+时间*/
			reserveDateTime.append((char*)row[2]);
        }
         
    } 
    else {
        printString( "Select date(reserve_time), TIME_TO_SEC(reserve_time) from reserve_list where reserve_time = (select min(reserve_time) from reserve_list) and reserve_status = 0; failed!!!!" ,LVS_COLOR_LIGHTRED,0);  
        goto ERROR_PROC;
    }  

    sqlstr = "Select datediff('";
    sqlstr.append(reserveDate);
    sqlstr.append("','");
    sqlstr.append(sysDateStr);
    sqlstr.append("');");

    if (0 == mysql_query(mysqlData, sqlstr.c_str())) {  
        printString( "Select datediff succeed" ,LVS_COLOR_WHITE,0);    

        //一次性取得数据集  
        mysql_free_result(result);
        result = mysql_store_result(mysqlData);  

        MYSQL_ROW row = NULL;
        row = mysql_fetch_row(result);  
        LVS_UINT32 rowcount = (LVS_UINT32)mysql_num_rows(result);
        
        /*查不到*/
        if(0 == rowcount) 
        {
            printString("查不到 in Select datediff !!", LVS_COLOR_LIGHTRED, 0);
            goto ERROR_PROC;
        }
        else 
        {
            /*取日期差值*/
            dateDiff = changeStringToUlong(row[0]);                        
        }
         
    } 
    else {
        printString( "Select datediff; failed!!!!" ,LVS_COLOR_LIGHTRED,0);  
        goto ERROR_PROC;
    }  
    mysql_free_result(result);
	closeConnectDb(mysqlData);
	mysqlData = LVS_NULL_PTR;
    
    /*返回预约时间 - 当前时间，返回值为秒数*/
	retTimeSec = dateDiff*60*60*24 + reserveTimeToSec - sysHour*3600 - sysMinute*60 - sysSecond;
	str = "最早未处理预约时间为: ";
	str.append(reserveDateTime);
	str.append(" 和当前时间 ");
	str.append(sysDateStr);
	str.append(" ");
	str.append(changeLongToString(sysHour));
	str.append(":");
	str.append(changeLongToString(sysMinute));
	str.append(":");
	str.append(changeLongToString(sysSecond));
	str.append(" 差的秒数为: ");
	str.append(changeLongToString((long) retTimeSec));
	str.append(" 秒。");
	printString(str, LVS_COLOR_WHITE,LVS_FALSE);

	if(0 > retTimeSec)
	{
		return 10 * 1000; /*如果为负数则返回10秒*/
	}
    return retTimeSec * 1000;
    
ERROR_PROC:
    mysql_free_result(result);
	closeConnectDb(mysqlData);
	mysqlData = LVS_NULL_PTR;
    return -1;    
}


LVS_UINT32 getTheRecentReserveInfo(CC_RESERVE_INFO_STRU *pReserveInfo)
{
	if(LVS_NULL_PTR == pReserveInfo)
    {
    	return -1;
	}

    unsigned long ulRet = 0;
    //连接数据库
	MYSQL *mysqlData = NULL;
	connectDb(&mysqlData);

    //sql字符串  
    string sqlstr;   
    LVS_UINT32 length = -1;
    LVS_UINT32 recentReserveId = -1;
    MYSQL_RES *result = NULL;  
    
    sqlstr = "select task_list_id from reserve_list where reserve_time = (select MAX(reserve_time) from reserve_list where reserve_status = 0);";
    if (0 == mysql_query(mysqlData, sqlstr.c_str())) {  
        printString( "Select most recent undo reserve id succeed" ,LVS_COLOR_WHITE,0);    

        //一次性取得数据集  
        result = mysql_store_result(mysqlData);  

        MYSQL_ROW row = NULL;
        row = mysql_fetch_row(result);  
        LVS_UINT32 rowcount = (LVS_UINT32)mysql_num_rows(result);
        
        /*查不到*/
        if(0 == rowcount) 
        {
            printString("查不到 Select most recent undo reserve id !!", LVS_COLOR_LIGHTRED, 0);
            goto ERROR_PROC;
        }
        else 
        {
            /*取最近一条未处理预约id*/
            recentReserveId = changeStringToUlong(row[0]);
            pReserveInfo->reserveId = recentReserveId;
        }
         
    } 
    else {
        printString( "Select most recent undo reserve id failed!!!!" ,LVS_COLOR_LIGHTRED,0);  
        goto ERROR_PROC;
    }
    
    sqlstr = "Select reserve_phone_num, reserve_time, reserve_department from reserve_list where task_list_id = ";
    sqlstr.append(changeLongToString((long)recentReserveId));
    sqlstr.append(";");
    if (0 == mysql_query(mysqlData, sqlstr.c_str())) {  
        printString( "Select reserve_phone_num, reserve_time, reserve_department from reserve_list succeed" ,LVS_COLOR_WHITE,0);    

        //一次性取得数据集  
        mysql_free_result(result);
        result = mysql_store_result(mysqlData);  

        MYSQL_ROW row = NULL;
        row = mysql_fetch_row(result);  
        LVS_UINT32 rowcount = (LVS_UINT32)mysql_num_rows(result);
        
        /*查不到或者多条记录*/
        if(0 == rowcount || 1 < rowcount ) 
        {
            printString("查不到或者多条记录 Select reserve_phone_num, reserve_time, reserve_department from reserve_list !!", LVS_COLOR_LIGHTRED, 0);
            goto ERROR_PROC;
        }
        else 
        {
            /*取来电号码*/
			if(LVS_NULL_PTR == row[0]){}
			else
			{
	            if(strlen(row[0]) > sizeof(pReserveInfo->callerPhoneNumber))
	            {
	                length = sizeof(pReserveInfo->callerPhoneNumber);
	            }
	            else
	            {
	                length = strlen(row[0]);
	            }            
	            memcpy(pReserveInfo->callerPhoneNumber,row[0],length);
			}
            /*取预约时间*/
			if(LVS_NULL_PTR == row[1]){}
			else
			{
	            if(strlen(row[1]) > sizeof(pReserveInfo->reserveTime))
	            {
	                length = sizeof(pReserveInfo->reserveTime);
	            }
	            else
	            {
	                length = strlen(row[1]);
	            }            
	            memcpy(pReserveInfo->reserveTime,row[1],length);
			}
            /*取取预约部门*/
			if(LVS_NULL_PTR == row[2]){}
			else
			{
	            if(strlen(row[2]) > sizeof(pReserveInfo->department))
	            {
	                length = sizeof(pReserveInfo->department);
	            }
	            else
	            {
	                length = strlen(row[2]);
	            }            
	            memcpy(pReserveInfo->department,row[2],length);            
			}
        }
         
    } 
    else {
        printString( "Select reserve_phone_num, reserve_time, reserve_department from reserve_list failed!!!!" ,LVS_COLOR_LIGHTRED,0);  
        goto ERROR_PROC;
    }
    mysql_free_result(result);

    sqlstr = "update reserve_list set reserve_status = 1 where task_list_id = ";
    sqlstr.append(changeLongToString((long)recentReserveId));
    sqlstr.append(";");

    if (0 == mysql_query(mysqlData, sqlstr.c_str())) {  
        printString( "mysql_query() update reserve_list task_status succeed" ,LVS_COLOR_WHITE,0);    
    } 
    else {
        printString( "mysql_query() update reserve_list task_status failed!!!!" ,LVS_COLOR_LIGHTRED,0);  
        goto ERROR_PROC;
    }      
    closeConnectDb(mysqlData);
	mysqlData = LVS_NULL_PTR;

	return LVS_OK;
	
ERROR_PROC:
    mysql_free_result(result);
	closeConnectDb(mysqlData);
	mysqlData = LVS_NULL_PTR;
    return -1;    
}
