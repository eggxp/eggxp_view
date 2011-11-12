gCurLine = 0
gLines = []
gResultClasses = {}
gListDict = {}
gClassNameHaveEntry = {}
gPassClassNames = {'GtOCTRegenMP':0,
                   'ItemDisplayInfo':0,
                   'AchievementCategory':0
                   }

gMemberTypeDict = {}

def ProcessClass(classStr):
    global gResultClasses
    global gListDict
    global gMemberTypeDict
    global gClassNameHaveEntry
    realclass = []
    for line in classStr:
        if line.find("(") != -1:
            break
        if line.strip() == "{":
            continue
        if line.strip() == "};":
            continue
        realclass.append(line)

    realclass[0] = realclass[0].replace("struct", "")
    realclass[0] = realclass[0].strip()
    if realclass[0].find("Entry") != -1:
        realclass[0] = realclass[0][:-5]
        gClassNameHaveEntry[realclass[0]] = 0
    className = realclass[0]
    if gPassClassNames.has_key(className) :
        return
    gResultClasses[className] = []
    del realclass[0]
    for line in realclass:
        line = line.strip()
        while line.find("  ") != -1:
            line = line.replace("  ", " ")
        line = line.replace("*", "")
        line = line.replace(";", "")
        lineSplit = line.split(" ")
        line = lineSplit[1]
        memberType = lineSplit[0]
        if line.find("[") == -1:
            gResultClasses[className].append(line)
            gMemberTypeDict[line] = memberType
            continue
        value = line.split("[")[1]
        value = value.replace("]", "")
        for i in range(int(value)):
            curLine = "%s_%s"%(line.split("[")[0], i)
            gListDict[curLine] = "%s[%s]"%(line.split("[")[0], i)
            gResultClasses[className].append(curLine)
            gMemberTypeDict[curLine] = memberType

    return

def ReadClass():
    global gLines
    global gCurLine
    classStr = []
    for i in range(gCurLine, len(gLines)):
        classStr.append(gLines[i])
        if gLines[i].find("}") != -1:
            gCurLine = i
            ProcessClass(classStr)
            break

def ProcessSource():
    global gLines
    f = file("dbc.txt")
    readLines = f.readlines()
    skip = 0
    for i in range(0, len(readLines)):
        readLines[i] = readLines[i].replace("\n", "")
        splitResult = readLines[i].split("//")
        readLines[i] = splitResult[0]
        if readLines[i].strip() == "":
            continue
        if readLines[i].find("/*") != -1:
            skip = 1
            continue
        if skip == 1:
            if readLines[i].find("*/") != -1:
                skip = 0
            continue
        gLines.append(readLines[i])

def main():
    ProcessSource()
    global gLines
    global gCurLine
    gCurLine = 0
    while gCurLine < len(gLines):
        if gLines[gCurLine].find("struct") != -1:
            ReadClass()
            continue
        else:
            gCurLine+=1

def PrintValues():
    global gResultClasses
    
    for key in gResultClasses.keys():
        print "    {"
        print "    tagDBCTableContent values;"
        for line in gResultClasses[key]:
            print '    values.Columns.push_back("%s");'%line
        print '    gTableColumns["%s"] = values;'%key
        print "    }"
    print ""

def GenOutputFunc():
    global gResultClasses
    global gClassNameHaveEntry
    global gListDict
    for key in gResultClasses.keys():
        curKey = key
        if gClassNameHaveEntry.has_key(curKey):
            curKey = "%sEntry"%curKey
        print "void %s_Output(const %s *input, TStrings *output)"%(key, curKey)
        print "{"
        print "    if(!input) return;"
        for line in gResultClasses[key]:
            curLine = line
            if gListDict.has_key(curLine):
                curLine = gListDict[curLine]
            
            if gMemberTypeDict[line] == "char":
                print '    output->Add(tlbm_UTF8ToAnsi(input->%s, strlen(input->%s)));'%(curLine, curLine)
            else:
                print "    output->Add(input->%s);"%curLine
        print "}"

def GetGetStoresCount():
    for key in gResultClasses.keys():
        print '    if(tableName == "%s")'%key
        print "        return Get%sStore()->GetRecordCount();"%key

def GetAddItems():
    for key in gResultClasses.keys():
        print '    if(tableName == "%s")'%key
        print "        %s_Output(Get%sStore()->LookupByIndex(index), output);"%(key, key)

def GetReadDefFunc():
    for key in gResultClasses.keys():
        print 'MANGOS_DLL_SPEC DBCStorage<%sEntry>  const* Get%sStore();'%(key, key)

def GetReadFunc():
    for key in gResultClasses.keys():
        print 'MANGOS_DLL_SPEC DBCStorage<%sEntry>  const* Get%sStore(){return &s%sStore;}'%(key, key, key)
main()
#PrintValues()
#GenOutputFunc()
#GetGetStoresCount()
GetAddItems()
#GetReadDefFunc()
#GetReadFunc()
