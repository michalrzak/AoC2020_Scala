

object Task1 {
    
    def adjacent(x:Int, y:Int):Int = {
        var count = 0

        if (x!=0 && data(y).charAt(x-1) == '#')
            count+=1
        
        if (x!=0 && y!=data.size-1 && data(y+1).charAt(x-1) == '#')
            count+=1

        if (y!=data.size-1 && data(y+1).charAt(x) == '#')
            count+=1

        if (x!=data(0).size-1 && y!=data.size-1 && data(y+1).charAt(x+1) == '#')
            count+=1
        
        if (x!=data(0).size-1 && data(y).charAt(x+1) == '#')
            count+=1

        if (x!=data(0).size-1 && y!=0 && data(y-1).charAt(x+1) == '#')
            count +=1

        if (y!=0 && data(y-1).charAt(x) == '#')
            count+=1

        if(x!=0 && y!=0 && data(y-1).charAt(x-1) == '#')
            count+=1

        count
    }

    var data = io.Source.fromFile("input.txt").getLines().toArray
    def main(args:Array[String]):Unit = {

        var dataChanged:Array[String] = new Array[String](data.size)
        data.copyToArray(dataChanged)

        var cont = true
        while(cont){
            cont = false
            for (y <- 0 to data.size-1){
                var x = 0
                dataChanged(y) = dataChanged(y).map(c => {
                    val adj = adjacent(x, y)
                    x+=1

                    if (c == '.')
                        c
                    else if (c == 'L' && adj==0){
                        cont = true
                        '#'
                    } else if (c == '#' && adj>=4) {
                        cont = true
                        'L'
                    } else
                        c
                })
                //println(data(y))
            }
            dataChanged.copyToArray(data)

            data.foreach(x => println(x))
            println("")
        }

        var count = 0
        data.foreach(line => count += line.count(c => c == '#'))
        println(count)
    }

}