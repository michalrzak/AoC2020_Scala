import scala.io.Source

object Task1 {
    
    lazy val data = Source.fromFile("input.txt").getLines().map(x => x.toLong).toArray

    def main(args:Array[String]) = {
        val preamble = 25
        var i = preamble
        var cont = true 

        while(cont && i < data.length){
            i+=1
            cont = false
            for(j <- i-preamble-1 to i-1){
                for (k <- j to i-1){
                    if(data(i) == data(j) + data(k))
                        cont = true
                }
            }
        }

        println(data(i))
    }

}