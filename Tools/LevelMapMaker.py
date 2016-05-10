import sys

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

    
    def insert(self, level, posStr):
        '''Returns insertion success'''
        col = ord(posStr[0]) - 65
        row = int(posStr[1])

        if not self.canInsert(level, row, col):
            return False

        for i in range(row, row + level.height):
            for j in range(col, col + level.width):
                self.grid[i][j] = level.id

        self.levels[level.id] = (level, posStr)

        return True


    def remove(self, levelID):
        for r in range(self.numRows):
            for c in range(self.numCols):
                if self.grid[r][c] == levelID:
                    self.grid[r][c] = -1

        del self.levels[levelID]



class LevelMapExporter:

    def __init__(self, levelMap):
        self.levelMap = levelMap

    def write(self, filepath):
        with open(filepath, 'w') as f:
            for r in range(self.levelMap.numRows):
                for c in range(self.levelMap.numCols):
                    f.write("{:2d} ".format(self.levelMap.grid[r][c]))
                f.write("\n")


class LevelMapSaver:
    def __init__(self, levelMap):
        self.levelMap = levelMap

    def save(self, filepath):
        with open(filepath, 'w') as f:
            for k,v in self.levelMap.levels.items():
                level = v[0]
                posStr = v[1]
                f.write("{} {} {} {}\n".format(level.id, level.width, level.height, posStr))


class LevelMapLoader:

    def load(self, filepath):
        #aww shit
        levelMap = LevelMap(rows = 20, cols = 40) #fix this later
        with open(filepath, 'r') as f:
            for line in f.readlines():
                splitline = line.split()
                newLevel = Level(int(splitline[0]), int(splitline[1]), int(splitline[2]))
                pos = splitline[3]
                levelMap.insert(newLevel, pos)

        return levelMap


if __name__ == '__main__':
    quitLoop = False
    levelMap = LevelMap(rows = 10, cols = 10)
    while (not quitLoop):
        print(levelMap)
        inputStr = raw_input()
        args = inputStr.split();
        
        if (args[0] == "create"):
            if (len(args) > 2):
                levelMap = LevelMap(rows = int(args[1]), cols = int(args[2]))
            else:
                print("Bad syntax: use 'create #rows #cols'")
        elif (args[0] == "insert"):
            print ("Please add new level: ")
            levelid = int(raw_input("levelid: "))
            width = int(raw_input("width: "))
            height = int(raw_input("height: "))
            level = Level(levelid, width, height)

            coord = raw_input("Where to insert? (Example: D6) : ")
            if levelMap.insert(level, coord):
                print("Insertion successful")
            else:
                print("No space to insert there")
        elif (args[0] == "remove"):
            if (len(args) > 1):
                levelMap.remove(int(args[1]))
            else:
                print("Bad syntax: use 'remove #levelid'")
        elif (args[0] == "clear"):
            levelMap = LevelMap(levelMap.numRows, levelMap.numCols)
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
        elif (args[0] == "export"):
            if len(args) > 1:
                LevelMapExporter(levelMap).write(args[1])
                print("File exported to '{}'. You may also want to save".format(args[1]))
            else:
                print("Missing file path argument")
        elif (args[0] == "quit"):
            quitLoop = True
        else:
            print("Unknown command. Command must be one of: create, insert, remove, clear, save, load, export, quit")
