

object Task1 {

    lazy val input = io.Source.fromFile("input.txt").getLines()
    def main(args:Array[String]) = {
        val timestamp:Long = input.next().toInt

        
        val ids = input.next().split(',').filterNot(ele => ele=="x")
        val ans = ids.minBy(ele => {
            val id = ele.toLong
            val arrives = (timestamp.toDouble/id).ceil * id
            arrives
        })

        val id = ans.toInt

        println((((timestamp.toDouble/id).ceil * id)-timestamp)*id)
    }
}