/* 
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */


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


 