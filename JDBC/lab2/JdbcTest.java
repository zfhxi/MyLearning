import java.sql.*;
//连接方法3需要添加
import java.util.*;

public class JdbcTest{
    //JDBC 驱动器名称 和数据库地址
    static final String JDBC_DRIVER="com.mysql.jdbc.Driver";
    //数据库的名称为 EXAMPLE
    static final String DB_URL="jdbc:mysql://localhost/EXAMPLE";

    //数据库用户和密码
    static final String USER="root";
    static final String PASS="";
    public static void main(String args[]){
        Connection conn=null;
        Statement stmt=null;
        try{
            //注册JDBC驱动程序
            //方法1
            //Class.forName(JDBC_DRIVER);
            //方法2
            Driver jdb_driver=new com.mysql.jdbc.Driver();
            DriverManager.registerDriver(jdb_driver);

            //打开链接
            System.out.println("Connection to database...");
            //方法1
            //conn=DriverManager.getConnection(DB_URL,USER,PASS);
            //方法2
            //String sqlurl="jdbc:mysql://localhost/EXAMPLE?user=root&password=";
            //conn=DriverManager.getConnection(sqlurl);
            //方法3
            Properties sqlpro=new Properties();
            //Properties对象，保存一组关键字-值对
            sqlpro.put("user","root");
            sqlpro.put("password","");
            conn=DriverManager.getConnection(DB_URL,sqlpro);

            //执行查询
            System.out.println("Creating statement...");
            stmt=conn.createStatement();
            String sql;
            sql="SELECT id,name,age FROM Students";
            ResultSet rs=stmt.executeQuery(sql);

            //得到和处理结果集
            while(rs.next()){
                //检索
                int id=rs.getInt("id");
                int age=rs.getInt("age");
                String name=rs.getString("name");

                //显示
                System.out.print("ID: "+id);
                System.out.print(", Age: "+age);
                System.out.print(", name: "+name);
                System.out.println();
            }
            //清理环境
            rs.close();
            stmt.close();
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
                if(stmt!=null)
                    stmt.close();
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
