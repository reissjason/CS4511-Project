<%-- 
    Document   : index
    Created on : May 16, 2012, 10:52:36 AM
    Author     : jason
--%>

<%@page import="org.apache.tomcat.jni.File"%>
<%@page import="java.io.*"%>
<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <link rel="shortcut icon" href="favico.ico" >
        <title>Qorkboard.com</title>
        <link rel="stylesheet" href="style.css" >
        <script type='text/javascript' src="jquery.js"></script>
        <script type="text/javascript" src="app.js"></script>
    </head>
    <body>
        <h1>Pokemon Battle Simulator</h1>
        <form>
            Pick three for each team.<br/>
            <% 
            
            String[] pokemons = { "Charizard", "Roserade", "Slowbro", "Ambipom", "Yanmega", "Porygon2" };
            
            if (request.getParameter("token") != null) {
               // out.println("<input type=\"radio\" name=\"game_type\" value=\"1\" " + ((request.getParameter("game_type").contains("1")) ? "checked" : "notchecked") + "/>Minimax Look Ahead(this game might take a while or crash)<br/>");
               // out.println("<input type=\"radio\" name=\"game_type\" value=\"2\" " + ((request.getParameter("game_type").contains("2")) ? "checked" : "notchecked") + " />Minimax Max Damage<br/>");
            %>
            <div style="float:left;margin:5px;margin-left:10px;">
                Team 1</br>
                <% for (int i=0; i<6; i++)
                    out.println("<input type='checkbox' name='team1_" + i + "' value='" + i + "' " + ((request.getParameter("team1_" + i) != null) ? "checked" : "") + "/>" + pokemons[i] + "<br/>");
                    %>
            </div>

            <div  style="float:left;margin:5px;margin-left:10px;margin-bottom:20px;">
                Team 2</br>
                <% for (int i=0; i<6; i++)
                    out.println("<input type='checkbox' name='team2_" + i + "' value='" + i + "' " + ((request.getParameter("team2_" + i) != null) ? "checked" : "") + "/>" + pokemons[i] + "<br/>");
                    %>
 
            </div>

            <% } else { %>
                        
            <div style="float:left;margin:5px;margin-left:10px;">
                Team 1</br>
                <input type="checkbox" name="team1_0" value="0" checked/>Charizard<br/>
                <input type="checkbox" name="team1_1" value="1" checked/>Roserade<br/>
                <input type="checkbox" name="team1_2" value="2" checked/>Slowbro<br/>
                <input type="checkbox" name="team1_3" value="3" />Ambipom<br/>
                <input type="checkbox" name="team1_4" value="4" />Yanmega<br/>
                <input type="checkbox" name="team1_5" value="5" />Porygon2<br/>
            </div>

            <div  style="float:left;margin:5px;margin-left:10px;margin-bottom:20px;">
                Team 2</br>
                <input type="checkbox" name="team2_0" value="0" />Charizard<br/>
                <input type="checkbox" name="team2_1" value="1" />Roserade<br/>
                <input type="checkbox" name="team2_2" value="2" />Slowbro<br/>
                <input type="checkbox" name="team2_3" value="3" checked/>Ambipom<br/>
                <input type="checkbox" name="team2_4" value="4" checked/>Yanmega<br/>
                <input type="checkbox" name="team2_5" value="5" checked/>Porygon2<br/>
            </div>
            <% } %>
            <div style="clear:both"/>
            <input type=hidden name="token" value="1"/>
            <input type="submit"/>
        </form>

        <hr/><hr/>
        <%

            if (request.getParameter("token") != null) {
                String team = "";

                for (int j = 1; j < 3; j++) {
                    for (int i = 0; i < 6; i++) {
                        if (request.getParameter("team" + j + "_" + i) != null) {
                            team += request.getParameter("team" + j + "_" + i);
                        }
                        if (team.length() == 3 * j) {
                            break;
                        }
                    }
                }

                boolean team_error = false;

                if (team.length() < 6) {
                    team_error = true;
                    out.println("<h2>Not enough Pokemon choosen</h2>");
                }


                Runtime r = Runtime.getRuntime();
                Process p = null;

                try {
                    int i = Integer.parseInt(team);
                } catch (Exception e) {
                    out.println("<h2>invalid team</h2>");
                    team_error = true;
                }

                if (!team_error) {
//                    if (request.getParameter("game_type").contains("1"))
//                        out.println("<h3>run with Look Ahead</h3><br/>");
//                    else
//                        out.println("<h3>run with Max Damage</h3><br/>");
                    try {
                        out.println("<xml id='data' style='display:none;'><document>");
                        
                        //p = r.exec("/home/jason/UMN/cs4511/CS4511-Project/minimax_game2 " + team);
                        
                        
                        // regulare minimax_game sucks too much resources on server
                        // disable option until game is fixed
                        
 //                       if (request.getParameter("game_type").contains("1"))
 //                          p = r.exec("/var/lib/tomcat6/webapps/ROOT/minimax_game " + team);  
 //                       else
                          p = r.exec("/var/lib/tomcat6/webapps/ROOT/minimax_game2 " + team);

                        // Open the file that is the first 
                        // command line parameter
                        //FileInputStream fstream = new FileInputStream("new_file");
                        // Get the object of DataInputStream
                        //DataInputStream in = new DataInputStream(fstream);
                        BufferedReader br = new BufferedReader(new InputStreamReader(p.getInputStream()));
                        String strLine;
                        //Read File Line By Line  
                        while ((strLine = br.readLine()) != null) {
                            // Print the content on the console
                            out.println("<line>" + strLine + "</line>");
                        }
                        
                        out.println("</document></xml>");
                    } catch (Exception e) {
                        out.println(e.getMessage());
                    }
                }
            }
        %>
        <div id='content'>
        </div>
    </body>
</html>
