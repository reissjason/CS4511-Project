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
        <title>Qorkboard.com</title>
        <style>
            .team_roster {
                min-width: 200px;
                float: left;
                border: 1px solid black;
                margin: 5px;
                padding: 5px;
                background: rgb(246,230,180); /* Old browsers */
                background: -moz-radial-gradient(center, ellipse cover,  rgba(246,230,180,1) 0%, rgba(237,144,23,1) 100%); /* FF3.6+ */
                background: -webkit-gradient(radial, center center, 0px, center center, 100%, color-stop(0%,rgba(246,230,180,1)), color-stop(100%,rgba(237,144,23,1))); /* Chrome,Safari4+ */
                background: -webkit-radial-gradient(center, ellipse cover,  rgba(246,230,180,1) 0%,rgba(237,144,23,1) 100%); /* Chrome10+,Safari5.1+ */
                background: -o-radial-gradient(center, ellipse cover,  rgba(246,230,180,1) 0%,rgba(237,144,23,1) 100%); /* Opera 12+ */
                background: -ms-radial-gradient(center, ellipse cover,  rgba(246,230,180,1) 0%,rgba(237,144,23,1) 100%); /* IE10+ */
                background: radial-gradient(center, ellipse cover,  rgba(246,230,180,1) 0%,rgba(237,144,23,1) 100%); /* W3C */
                filter: progid:DXImageTransform.Microsoft.gradient( startColorstr='#f6e6b4', endColorstr='#ed9017',GradientType=1 ); /* IE6-9 fallback on horizontal gradient */

            }

            .team_roster h2 {
                text-align: center;
            }

            div {
                margin: 3px;
            }

            .clear {
                clear: both;
            }

            h4, .attack, .KO, table td {
                text-transform: capitalize;
            }

            table {
                margin-left: auto; 
                margin-right:auto;
                border-collapse:collapse; 
            }

            table th {
                border-bottom: 2px solid black;
            }

            table td {
                padding: 10px;
            }

            .attack {
                width: 500px;
                bottom-margin: 3px;
                border: 1px solid black;
                background: rgb(254,252,234); /* Old browsers */
                background: -moz-linear-gradient(-45deg,  rgba(254,252,234,1) 0%, rgba(241,218,54,1) 100%); /* FF3.6+ */
                background: -webkit-gradient(linear, left top, right bottom, color-stop(0%,rgba(254,252,234,1)), color-stop(100%,rgba(241,218,54,1))); /* Chrome,Safari4+ */
                background: -webkit-linear-gradient(-45deg,  rgba(254,252,234,1) 0%,rgba(241,218,54,1) 100%); /* Chrome10+,Safari5.1+ */
                background: -o-linear-gradient(-45deg,  rgba(254,252,234,1) 0%,rgba(241,218,54,1) 100%); /* Opera 11.10+ */
                background: -ms-linear-gradient(-45deg,  rgba(254,252,234,1) 0%,rgba(241,218,54,1) 100%); /* IE10+ */
                background: linear-gradient(-45deg,  rgba(254,252,234,1) 0%,rgba(241,218,54,1) 100%); /* W3C */
                filter: progid:DXImageTransform.Microsoft.gradient( startColorstr='#fefcea', endColorstr='#f1da36',GradientType=1 ); /* IE6-9 fallback on horizontal gradient */
                color: #6d0019;
                font-weight: bold;	
            }

            .KO {

            }

            body {
                background: -moz-linear-gradient(-45deg,  rgba(254,254,253,0.56) 0%, rgba(220,227,196,0.53) 42%, rgba(174,191,118,0.48) 100%); /* FF3.6+ */
                background: -webkit-gradient(linear, left top, right bottom, color-stop(0%,rgba(254,254,253,0.56)), color-stop(42%,rgba(220,227,196,0.53)), color-stop(100%,rgba(174,191,118,0.48))); /* Chrome,Safari4+ */
                background: -webkit-linear-gradient(-45deg,  rgba(254,254,253,0.56) 0%,rgba(220,227,196,0.53) 42%,rgba(174,191,118,0.48) 100%); /* Chrome10+,Safari5.1+ */
                background: -o-linear-gradient(-45deg,  rgba(254,254,253,0.56) 0%,rgba(220,227,196,0.53) 42%,rgba(174,191,118,0.48) 100%); /* Opera 11.10+ */
                background: -ms-linear-gradient(-45deg,  rgba(254,254,253,0.56) 0%,rgba(220,227,196,0.53) 42%,rgba(174,191,118,0.48) 100%); /* IE10+ */
                background: linear-gradient(-45deg,  rgba(254,254,253,0.56) 0%,rgba(220,227,196,0.53) 42%,rgba(174,191,118,0.48) 100%); /* W3C */
                filter: progid:DXImageTransform.Microsoft.gradient( startColorstr='#8ffefefd', endColorstr='#7aaebf76',GradientType=1 ); /* IE6-9 fallback on horizontal gradient */

            }

            .winner {
                border: 1px solid grey;
                font-size: 30px;
                margin: 10px;
                background: green;
                font-weight: bold;
                margin-bottom: 100px;
                text-align: center;
            }

            .summary {
                border: 2px solid black;
                padding: 3px;
                margin: 4px;
                width: 500px;
                margin-top: 10px;
                text-transform: capitalize;
            }

            .switching {
                width: 500px;
                background: -moz-linear-gradient(-45deg,  rgba(30,87,153,1) 0%, rgba(125,185,232,0) 100%); /* FF3.6+ */
                background: -webkit-gradient(linear, left top, right bottom, color-stop(0%,rgba(30,87,153,1)), color-stop(100%,rgba(125,185,232,0))); /* Chrome,Safari4+ */
                background: -webkit-linear-gradient(-45deg,  rgba(30,87,153,1) 0%,rgba(125,185,232,0) 100%); /* Chrome10+,Safari5.1+ */
                background: -o-linear-gradient(-45deg,  rgba(30,87,153,1) 0%,rgba(125,185,232,0) 100%); /* Opera 11.10+ */
                background: -ms-linear-gradient(-45deg,  rgba(30,87,153,1) 0%,rgba(125,185,232,0) 100%); /* IE10+ */
                background: linear-gradient(-45deg,  rgba(30,87,153,1) 0%,rgba(125,185,232,0) 100%); /* W3C */
                filter: progid:DXImageTransform.Microsoft.gradient( startColorstr='#1e5799', endColorstr='#007db9e8',GradientType=1 ); /* IE6-9 fallback on horizontal gradient */
                text-transform: capitalize;
                color: white;
                font-weight: bold;
            }

            a, a:visited {
                color: blue;
            }

            a:hover {
                color: #101010;
            }
        </style>
        <script type='text/javascript' src="jquery.js"></script>
        <script type="text/javascript">
            
            $(document).ready(function() {
                parser=new DOMParser();
                console.log($("#data").html());
                xmlDoc=parser.parseFromString($("#data").html(),"text/xml");
                display_page(xmlDoc);
            
            });
            
            function display_page(data) {
                $("#content").hide();
	
                var lines =  data.documentElement.childNodes;
                $("#content").html("");
 			
                var round = "1";
                var team_members = 1;
                var team_cnt = 1;
                var str = "";
 			
                var save_str = "";
 			
                var cur_team = 0;
                var start_log = false;
 			
                var team_1_p = "";
                var team_2_p = "";
 			
                var summary = 0;
 			
 			
                for (item in lines) {
                    //$("#content").append(lines[item].nodeType);
                    if (lines[item].nodeType == 1) {
				
                        var _text = $.trim(lines[item].textContent);
                        console.log(_text);
                        if (_text.indexOf("Picked") >= 0) {
                            if (team_members == 1 || team_members == 4) {
                                str += "<div class=team_roster><h2>Team " + team_cnt + "</h2><table>";
                                str += "<tr><thead><th>Name</th><th>HP</th></thead></tr><tr><tbody>";
                            }
                            var parts = _text.split(" ");
				
                            str +="<tr><td>" + parts[1] + "</td><td>" + parts[3] + "</td></tr>";
						
                            if (team_members == 3 || team_members == 6)
                                str += "</tbody></table></div>";
							
                            if (team_members++ == 3) team_cnt++;
                            start_log = true;
						
                            continue;						
                        }
					
                        if (start_log) {
                            start_log = false;
                            str += "<div class=clear></div><h2>Battle Log</h2>";
                            continue;
                        }
					
                        if (_text.indexOf("Round") >= 0)
                            round = _text.split(" ")[1];					
					
                        if (_text.indexOf("******") >= 0)
                            str += "<hr><h3>Round " + round + "</h3>";
						
                        var parts = _text.split(" ");					
					
                        if (_text.indexOf(" vs ") >= 0) {
                            str += "<h4>" + _text + "</h4>";
                            team_1_p = parts[0];
                            team_2_p = parts[2];
                            continue;
                        }
					
                        if (_text.indexOf("Team 1 goes") >= 0 || _text.indexOf("Team 2 goes") >= 0) {
                            str += "<div class=team_start>" + parts[0] + " " + parts[1] + " Goes First</div>";
                            cur_team = parts[1];
                            continue;
                        }
				
                        if (_text.indexOf("attacks") >= 0) {
                            str += "<div class=attack>" + _text + "</div>";
						
                            if (save_str != "" && cur_team == "2") {
                                str+= save_str;
                                save_str = "";
                            }						
                            continue;
                        }
					
                        if (_text.indexOf("power") >= 0) {
                            if (cur_team == "2") cur_team = "1"; else cur_team = "2";
                            // str += "<br>" + cur_team + "</br>";
                            if (cur_team == "2")
                                save_str = "<div class=power>Attack Power: " + parts[parts.length-1] + "</div>";
                            else
                                str += "<div class=power>Attack Power: " + parts[parts.length-1] + "</div>";
                            continue;
                        }
					
                        if (_text.indexOf("pokemon KO") >= 0) {
                            if (_text.indexOf("Team 1") >= 0)
                                str += "<div class=ko>"+ team_1_p + " Knocked Out</div>";
                            else
                                str += "<div class=ko>"+ team_2_p + " Knocked Out</div>";
                            continue;
                        }
					
                        if (_text.indexOf("damage") >= 0) {
                            str += "<div class=damage>" + _text + "</div>";
                            continue;
                        }
						
                        if (_text.indexOf(" wins!") >= 0) {
                            var _str = "<div class=winner>" + _text + "</div>";
                            str += _str;
                            $("#content").append(_str);
                        }
					
                        if (_text.indexOf(" hp: ") >= 0) {
                            console.log("======== " + parts + " ==============");
                            if (summary++ == 0)
                                str += "<div class=summary><div>Round Summary</div>";
						 	
                            str += "<div>" + parts[0] + " : " + ((parts[2] > 0) ? (parts[2] + " HP") : "Fainted") + "</div>";
                            if (summary == 2) {
                                str += "</div><div><a href='#top'>Back To Top</a></div>";
                                summary = 0;
                            } 
                        }
					
                        if (_text.indexOf("switching ") >= 0) {
                            str += "<div class=switching>" + _text + "</div>";
                        }
                    }
                }
                console.log(str);			
                $("#content").append(str);
                setTimeout('$("#message").hide()', 500);
                setTimeout('$("#content").fadeIn("slow")', 500);
            }


 
        </script>


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
