import java.sql.*;
import java.util.*;

public class JdbcTest_CallableStatement{
    //JDBC 驱动器名称 和数据库地址
    static final String JDBC_DRIVER="com.mysql.jdbc.Driver";
    //数据库的名称为 EXAMPLE
    static final String DB_URL="jdbc:mysql://localhost/EXAMPLE";

    //数据库用户和密码
    static final String USER="root";
    static final String PASS="";
    public static void main(String args[]){
        Connection conn=null;
        CallableStatement cstmt=null;
        try{
            //注册JDBC驱动程序
            Driver jdb_driver=new com.mysql.jdbc.Driver();
            DriverManager.registerDriver(jdb_driver);

            //打开链接
            System.out.println("Connection to database...");
            Properties sqlpro=new Properties();
            //Properties对象，保存一组关键字-值对
            sqlpro.put("user","root");
            sqlpro.put("password","");
            conn=DriverManager.getConnection(DB_URL,sqlpro);

            //执行存储过程
            System.out.println("Creating statement...");
            String sql;
            sql="{CALL mypro(?,?,?)}";
            cstmt=conn.prepareCall(sql);
            cstmt.setInt(1,100);
            cstmt.setInt(2,200);
            cstmt.registerOutParameter(2,Types.INTEGER);
            cstmt.registerOutParameter(3,Types.INTEGER);
            cstmt.execute();
            //执行查询
            System.out.println("INOUT的返回值:"+cstmt.getInt(2));
            System.out.println("OUT的返回值:"+cstmt.getInt(3));
            //清理环境
            cstmt.close();
            conn.close();
        }catch(SQLException se){
            //JDBC 操作错误
            se.printStackTrace();
        }catch(Exception e){
            //Class.forName错误
            e.printStackTrace();
        }finally{
            //这里一般用来关闭资源
            try{
                if(cstmt!=null)
                    cstmt.close();
            }catch(SQLException se2){}
            try{
                if(conn!=null)
                    conn.close();
            }catch(SQLException se){
                se.printStackTrace();
            }
        }
        System.out.println("Goodbye!");
    }
}
