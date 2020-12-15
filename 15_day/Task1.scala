


object Task1 {

    lazy val input = "18,8,0,5,4,1,20".split(',')
    def main (args:Array[String]) = {
        
        var vals:Map[Integer, Integer] = Map()
        var turn = 0
        
        //parse input
        input.foreach(ele => {
            vals(ele.toInt) += 1
            turn+=1
        })

        var curr = input.last.toInt

        for (i <- turn to 2020){
            println(vals(curr))
            vals(curr) += 1
        }


    }
}