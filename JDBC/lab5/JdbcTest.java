import java.sql.*;

public class JdbcTest {
    //JDBC 驱动器名称 和数据库地址
    static final String JDBC_DRIVER = "com.mysql.jdbc.Driver";
    //数据库的名称为EXAMPLE
    static final String DB_URL = "jdbc:mysql://localhost/EXAMPLE";

    //数据库用户和密码
    static final String USER = "root";
    static final String PASS = "";

    public static void main(String args[]) {
        Connection conn = null;
        Statement stmt = null;
        try {
            //注册JDBC驱动程序
            Class.forName(JDBC_DRIVER);

            //打开链接
            System.out.println("Connection to database...");
            conn = DriverManager.getConnection(DB_URL, USER, PASS);
            conn.setAutoCommit(false);

            //执行查询
            System.out.println("Creating statement...");
            stmt = conn.createStatement();
            //插入
            String sql = "INSERT INTO Students " + "VALUES (3,20,'ROSE')";
            stmt.executeUpdate(sql);
            //查找
            sql = "SELECT id, name, age FROM Students";
            ResultSet rs = stmt.executeQuery(sql);

            //提交事务
            conn.commit();

            //得到和 处理结果集
            int id, age;
            String name;
            while (rs.next()) {
                //检索
                id = rs.getInt("id");
                age = rs.getInt("age");
                name = rs.getString("name");

                //显示
                System.out.print("ID: " + id);
                System.out.print(", Age: " + age);
                System.out.print(", Name: " + name);
                System.out.println();
            }

            //清理环境
            rs.close();
            stmt.close();
            conn.close();
        } catch (SQLException se) {
            //JDBC 操作错误
            se.printStackTrace();
            //conn.rollback();
            try {
                if (conn != null)
                    conn.rollback();
            } catch (SQLException se2) {
                se2.printStackTrace();
            }
        } catch (Exception e) {
            //Calss.forName错误
            e.printStackTrace();
        } finally {
            //这一般是用来关闭资源的
            try {
                if (stmt != null)
                    stmt.close();
            } catch (SQLException se2) {

            } try {
                if (conn != null)
                    conn.close();
            } catch (SQLException se) {
                se.printStackTrace();
            }
        }
        System.out.println("GoodBye!");
    }
}
