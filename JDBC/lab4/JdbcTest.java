import java.sql.*;

public class JdbcTest {
    //JDBC 驱动器名称 和数据库地址
    static final String JDBC_DRIVER = "com.mysql.jdbc.Driver";
    //数据库的名称为 EXAMPLE
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

            //执行查询
            System.out.println("Creating statement...");
            //创建所需的ResultSet，双向，只读
            stmt = conn.createStatement(ResultSet.TYPE_SCROLL_INSENSITIVE, ResultSet.CONCUR_UPDATABLE);
            String sql;
            sql = "SELECT id,name,age FROM Students";
            ResultSet rs = stmt.executeQuery(sql);

            //将光标移动到最后一行
            System.out.println("Moving cursor to the last...");
            rs.last();

            //处理结果集
            System.out.println("Displaying record...");
            int id = rs.getInt("id");
            int age = rs.getInt("age");
            String name = rs.getString("name");

            //显示
            System.out.print("ID: " + id);
            System.out.print(", Age: " + age);
            System.out.print(", Name: " + name);
            System.out.println();

            //将光标移动到第一行
            System.out.println("Moving cursor to the first row...");
            rs.first();

            //再一次处理结果集
            System.out.println("Displaying record...");
            id = rs.getInt("id");
            age = rs.getInt("age");
            name = rs.getString("name");

            //显示
            System.out.print("ID: " + id);
            System.out.print(", Age: " + age);
            System.out.print(", Name: " + name);
            System.out.println();

            //结果集中插入新行
            rs.moveToInsertRow();
            rs.updateInt("id", 5);
            rs.updateString("name", "John");
            rs.updateInt("age", 21);
            //更新数据库
            rs.insertRow();

            //显示所有
            rs.first();
            while (rs.next()) {
                id = rs.getInt("id");
                age = rs.getInt("age");
                name = rs.getString("name");

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
        } catch (Exception e) {
            //Class.forName错误
            e.printStackTrace();
        } finally {
            //这里一般用来关闭资源
            try {
                if (stmt != null)
                    stmt.close();
            } catch (SQLException se2) {}
            try {
                if (conn != null)
                    conn.close();
            } catch (SQLException se) {
                se.printStackTrace();
            }
        }
        System.out.println("Goodbye!");
    }
}
