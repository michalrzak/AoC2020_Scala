
object Task1{

    lazy val in = io.Source.fromFile("input.txt").getLines().map(x => x.toInt).toArray.sortWith((x,y) => x < y).toArray

    def main(args:Array[String]) = {

        val input = in :+ in.last+3


        var prev:Int = 0
        val oneJolt = input.count(ele => {
            val ret = (ele-prev == 1)
            prev = ele
            ret
        })

        prev = 0
        val threeJolt = input.count(ele => {
            val ret = (ele-prev == 3)
            prev = ele
            ret
        }) //one smaller; not counting connection to device

        println(oneJolt * (threeJolt))
    }

}