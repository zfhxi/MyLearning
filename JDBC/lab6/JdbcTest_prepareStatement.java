import java.sql.*;

public class JdbcTest_prepareStatement {
    //JDBC 驱动器名称 和数据库地址
    static final String JDBC_DRIVER = "com.mysql.jdbc.Driver";
    //数据库的名称为EXAMPLE
    static final String DB_URL = "jdbc:mysql://localhost/EXAMPLE";

    //数据库用户和密码
    static final String USER = "root";
    static final String PASS = "";

    public static void main(String args[]) {
        Connection conn = null;
        PreparedStatement pstmt = null;
        try {
            //注册JDBC驱动程序
            Class.forName(JDBC_DRIVER);

            //打开链接
            System.out.println("Connection to database...");
            conn = DriverManager.getConnection(DB_URL, USER, PASS);

            //添加SQL
            System.out.println("Creating statement...");
            //删除数据
            String SQL = "DELETE FROM Students WHERE id=?";
            //创建PrepateStatement对象
            pstmt = conn.prepareStatement(SQL);
            //关闭自动连接
            conn.setAutoCommit(false);

            //绑定参数
            pstmt.setInt(1, 5); //去除id为5的元组
            //添加到批处理
            pstmt.addBatch();

            //去除id为6,、7的元组
            pstmt.setInt(1, 6);
            pstmt.addBatch();
            pstmt.setInt(1, 7);
            pstmt.addBatch();
            //创建整数数组记录更新情况
            int []count = pstmt.executeBatch();
            //提交事务
            conn.commit();

            //查找
            SQL = "SELECT id, name, age FROM Students";
            ResultSet rs = pstmt.executeQuery(SQL);


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

            System.out.println("Output the array count[]:");
            System.out.println(java.util.Arrays.toString(count));

            //清理环境
            rs.close();
            pstmt.close();
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
                if (pstmt != null)
                    pstmt.close();
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
