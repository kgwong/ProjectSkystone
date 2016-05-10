def posStr_to_row_col(posStr):
    col = ord(posStr[0]) - 65
    row = int(posStr[1:])
    return (row, col)

class Level:
    def __init__(self, id, width, height):
        self.id = id
        self.width = width
        self.height = height


class LevelMap:
    def __init__(self, rows, cols):
        self.grid = [[-1 for c in range(cols)] for r in range(rows)]
        self.numRows = rows
        self.numCols = cols
        self.levels = {}


    def __str__(self):
        result = "     "
        rowNum = 0

        for i in range(len(self.grid[0])):
            result += "{:>2} ". format(chr(i + 65))
        result += "\n\n"
        
        for row in self.grid:
            result += "{:2d}   ".format(rowNum)
            rowNum += 1
            for num in row:
                result += "{:2d} ".format(num)
            result += "\n"
        return result

    def canInsert(self, level, row, col):
        for i in range(row, row + level.height):
            for j in range(col, col + level.width):
                if self.grid[i][j] != -1:
                    return False
        return True

    
    def insert_with_str(self, level, posStr):
        '''Returns insertion success'''
        rc = posStr_to_row_col(posStr)
        row = rc[0]
        col = rc[1]

        return self.insert(level, row, col)

    def insert(self, level, row, col):
        if not self.canInsert(level, row, col):
            return False

        for i in range(row, row + level.height):
            for j in range(col, col + level.width):
                self.grid[i][j] = level.id

        self.levels[level.id] = (level, row, col)
        return True


    def remove(self, levelID):
        for r in range(self.numRows):
            for c in range(self.numCols):
                if self.grid[r][c] == levelID:
                    self.grid[r][c] = -1

        del self.levels[levelID]


class LevelMapSaver:
    def __init__(self, levelMap):
        self.levelMap = levelMap

    def save(self, filepath):
        with open(filepath, 'w') as f:
            f.write("{} {}\n".format(self.levelMap.numRows, self.levelMap.numCols))
            for k,v in self.levelMap.levels.items():
                level = v[0]
                row = v[1]
                col = v[2]
                f.write("{} {} {} {} {}\n".format(level.id, level.width, level.height, row, col))


class LevelMapLoader:
    def load(self, filepath):
        levelMap = None
        with open(filepath, 'r') as f:
            lines = f.readlines()
            rowscols = lines[0]
            rowscolssplit = rowscols.split()

            levelMap = LevelMap(rows=int(rowscolssplit[0]), cols=int(rowscolssplit[1]))

            for line in lines[1:]:
                print("loading")
                splitline = line.split()
                newLevel = Level(int(splitline[0]), int(splitline[1]), int(splitline[2]))
                row = int(splitline[3])
                col = int(splitline[4])
                levelMap.insert(newLevel, row, col)

        return levelMap


if __name__ == '__main__':
    quitLoop = False
    levelMap = LevelMap(rows = 10, cols = 10)
    print(levelMap)
    while (not quitLoop):
        print("Enter a command")
        print("print")
        print("create #rows #cols")
        print("insert")
        print("remove #levelID")
        print("clear")
        print("save filepath")
        print("load filepath")
        print("quit")
        print("> ", end="")
        inputStr = input()
        args = inputStr.split();

        if (args[0] == "print"):
            print(levelMap)
        
        elif (args[0] == "create"):
            if (len(args) > 2):
                levelMap = LevelMap(rows = int(args[1]), cols = int(args[2]))
                print(levelMap)
            else:
                print("Bad syntax: use 'create #rows #cols'")
                
        elif (args[0] == "insert"):
            print ("Please add new level: ")
            levelid = int(input("levelid: "))
            width = int(input("width: "))
            height = int(input("height: "))
            level = Level(levelid, width, height)

            coord = input("Where to insert? (Example: D6) : ")
            if levelMap.insert_with_str(level, coord):
                print(levelMap)
                print("Insertion successful")
            else:
                print("No space to insert there")
                
        elif (args[0] == "remove"):
            if (len(args) > 1):
                levelMap.remove(int(args[1]))
                print(levelMap)
                print("Removal successful")
            else:
                print("Bad syntax: use 'remove #levelid'")
                
        elif (args[0] == "clear"):
            levelMap = LevelMap(levelMap.numRows, levelMap.numCols)
            print(levelMap)
            
        elif (args[0] == "save"):
            if len(args) > 1:
                LevelMapSaver(levelMap).save(args[1])
                print("File saved to '{}'".format(args[1]))
            else:
                print("Missing file path argument")
                
        elif (args[0] == "load"):
            if len(args) > 1:
                levelMap = LevelMapLoader().load(args[1])
                print("Successfully loaded!")
            else:
                print("Please specify which file to load from")
                
        elif (args[0] == "quit"):
            quitLoop = True
            
        else:
            print("Unknown command. Command must be one of: print, create, insert, remove, clear, save, load, quit")
