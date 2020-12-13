import scala.util.control._


object Task2 {

    def findMultiple(Mi: Long, i: Long):Long = {
        var out:Long = 1
        while((Mi*out) % i != 1){
            //println((Mi*out) % i)
            out+=1
        }

        out
    }

    lazy val input = io.Source.fromFile("input.txt").getLines()
    def main(args:Array[String]) = {
        
        var skip = input.next().toInt

        val ids = input.next().split(',')
        
        val M:Long = ids.filterNot(ele => ele=="x").map(ele => ele.toLong).product
        println(M)

        var res:Long = 0
        
        for (i <- 1 to ids.length-1){
            if (ids(i) != "x"){
                val curr:Long = ids(i).toLong
                val Mi = M/curr
                println(Mi%curr)
                println(curr)
                res = res + (curr-i) * Mi * findMultiple(Mi%curr, curr)
            } 
        }

        res = res%M
        ids.filterNot(ele => ele=="x").map(ele => ele.toLong).foreach(ele => println(res%ele))
        println(res)

    }
}