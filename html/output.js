$(function()
{
  var table = $('#table');
  var grid = $('#gantt_grid');

  var process_n = Object.keys(g_process).length;
  var wait_time = 0;
  var turn_time = 0;
  
  var hue_table = new Array();

  for(var pid in g_process)
  {
    var proc = g_process[pid];
    var arrival = proc[0];
    var term = proc[1];
    var burst = proc[2];
    var pri = proc[3];
    var turn = term-arrival;
    var wait = turn-burst;
    var huen = hue_table.length;
    var procn = g_process.length;
    var hue = hue_table.length/process_n*360;
    hue_table[pid] = hue;
    wait_time += wait;
    turn_time += turn;
    
    table.append($('<tr id="proc_'+pid+'"><td>&nbsp;<span style="background-color:hsl('+hue+',100%,85%)">&nbsp;&nbsp;</span> '+pid+'</td><td>'+arrival+'</td><td>'+term+'</td><td>'+burst+'</td><td>'+pri+'</td><td>'+turn+'</td><td>'+wait+'</td></tr>').hover(
    function()
    {
      var pid = $(this).attr('id').split('proc_')[1];
      $('.ev_'+pid).toggleClass('ev-hover',true);
    },
    function()
    {
      var pid = $(this).attr('id').split('proc_')[1];
      $('.ev_'+pid).toggleClass('ev-hover',false);
    }));
  }
  
  wait_time /= process_n;
  turn_time /= process_n;
  $("#stat_proc").html(process_n);
  $("#stat_turn").html(turn_time);
  $("#stat_wait").html(wait_time);

  var end = 0;
  for(var i=0; i<g_event.length; ++i)
  {
    var event = g_event[i];
    var start = event[0];
    var stop = event[1];
    var pid = event[2];
    if(stop > end)
      end = stop;
    grid.append($('<div class="ev_'+pid+'">'+pid+'</div>').css({"top":40,"height":45,"left":start*20,"width":(stop-start)*20-1,'background-color':'hsl('+hue_table[pid]+',100%,85%)'}).mouseenter({ind:i},
    function(data)
    {
      var event = g_event[data.data.ind];
      var start = event[0];
      var stop = event[1];
      var pid = event[2];
      var pri = event[3];

      $('#proc_'+pid).toggleClass('proc-hover',true);
      
      $('#info-pid').html(pid);
      $('#info-pri').html(pri);
      $('#info-start').html(start);
      $('#info-stop').html(stop);
      $('#info').show();
    }).mouseleave({ind:i},
    function(data)
    {
      var event = g_event[data.data.ind];
      var pid = event[2];

      $('#proc_'+pid).toggleClass('proc-hover',false);
      $('#info').hide();
    }).mousemove(
    function(event)
    {
      $('#info').css({"top":event.pageY,"left":event.pageX});
    }));
  }
  grid.width(end*20+1);
  for(tick=0; tick<end; tick+=10)
  {
    grid.append($('<span></span>').html(tick).css({"top":2,"left":tick*20+4}));
  }
});