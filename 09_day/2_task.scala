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

        val invNumber = data(i)
        val invIndex = i


        i = 0
        cont = true
        while (cont && i < invIndex){
            var smallest:Long = 0
            var largest:Long = 0
            var sum:Long = 0
            for(j <- i to invIndex){
                sum+=data(j)
                if(sum == invNumber){
                    cont = false  
                    val smallest = data.drop(i).take(j-i).min
                    val largest  = data.drop(i).take(j-i).max

                    println(smallest + largest)
                }
            }
            i+=1
        }
    }

}