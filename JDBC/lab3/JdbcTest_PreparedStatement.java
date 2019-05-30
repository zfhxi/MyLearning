import java.sql.*;
import java.util.*;

public class JdbcTest_PreparedStatement{
    //JDBC 驱动器名称 和数据库地址
    static final String JDBC_DRIVER="com.mysql.jdbc.Driver";
    //数据库的名称为 EXAMPLE
    static final String DB_URL="jdbc:mysql://localhost/EXAMPLE";

    //数据库用户和密码
    static final String USER="root";
    static final String PASS="";
    public static void main(String args[]){
        Connection conn=null;
        PreparedStatement stmt=null;
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

            //执行查询
            System.out.println("Creating statement...");
            //此处更改同学的年龄，参数待定
            String sql;
            sql="UPDATE Students set age=? WHERE id=?";
            stmt=conn.prepareStatement(sql);
            //将值绑定到参数，参数从左到右序号为1,2,3,...
            stmt.setInt(1,30);//绑定age的值，序号为1
            stmt.setInt(2,4);//绑定id的值，序号为2
            //更新id为4的同学的年龄为30
            int rows=stmt.executeUpdate();
            System.out.println("被影响的行数："+rows);
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
