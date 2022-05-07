# importing necessary libraries
from asyncore import write
from distutils import extension
from fastapi import FastAPI, File, UploadFile, Response
from fastapi.responses import StreamingResponse
from fastapi.middleware.cors import CORSMiddleware
from pydantic import BaseModel
from colour import Color
import matplotlib
import matplotlib.pyplot as plot
import matplotlib.ticker as ticker
import matplotlib.font_manager as fm
import json
from encode import fctem_to_txt

app = FastAPI()

origins = [
    "http://localhost",
    "http://localhost:3000",
    "http://127.0.0.1",
    "http://127.0.0.1:3000",
    "http://47.108.115.41:3000",
]

app.add_middleware(
    CORSMiddleware,
    allow_origins=origins,
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)

class Item(BaseModel):
    path: str = None

@app.get("/api/get_argument_settings")
def getArgument():
    f = open('model.json', )
    data = json.load(f)
    return data

@app.post('/api/get_chart_info')
async def getChartInfo(request_data: Item):
    path = request_data.path
    base = "/Users/kevinlinpr/Documents/filesystem/"
    file = open(base + path)
    # 这里解码
    line = file.readline()
    info = line.split()
    pointNumb = int(eval(info[0]))
    windowNumb = int(eval(info[1]))
    return {
        'pointNumb': pointNumb,
        'windowNumb': windowNumb
    }

@app.post('/api/get_chart')
async def calculate(request_data: Item):
    path = request_data.path
    #
    # 微软雅黑,如果需要宋体,可以用simsun.ttc
    myfont = matplotlib.font_manager.FontProperties(fname='SimHei.ttf')

    plot.figure()  # creat a new figure
    myfig = plot.gcf()  # Get the current figure. If no current figure exists, a new one is created using figure().

    import numpy as np
    base = "/Users/kevinlinpr/Documents/filesystem/"
    fake = "/Users/kevinlinpr/Documents/filesystem/"
    # base = ""
    prehandler = path.split('/')
    file_name = prehandler[len(prehandler) - 1]
    extension_name = file_name.split('.')[1]

    tmp_txt_name = ''
    if extension_name == 'FCTEM' or extension_name == 'fctem':
        tmp_txt_name = fake + path + '.tmptxt'
        txt_context = fctem_to_txt(base + path)
        txt_file = open(tmp_txt_name,'w+')
        txt_file.write(txt_context)
        txt_file.close()
    else:
        tmp_txt_name = base + path
    
    
    file = open(tmp_txt_name)
    # 解码
    pathArr = path.split('/')
    resultName = pathArr[2] + '_' + pathArr[4] + '_' + pathArr[5] + '.png'
    savePath = pathArr[0] + '/' + pathArr[1] + '/' + pathArr[2] + '/结果/'
    resultPath = base + savePath + resultName
    line = file.readline()
    # print(line.split())
    info = line.split()
    rowInfo = info[0]
    columnInfo = info[1]
    print(int(eval(rowInfo)))
    print(int(eval(columnInfo)))
    file.seek(0)
    XArr = []
    pointArr = []
    lineCount = 0
    # while start
    while True:
        content = file.readline()
        if not content:
            break
        arr = content.split()
        if lineCount > 0:
            XArr.append(eval(arr[0]))
            tmp = []
            for index, item in enumerate(arr):
                if index > 1:
                    tmp.append(item)
            pointArr.append(tmp)
        lineCount += 1
    # while end
    # print(pointArr)
    grid = [([0] * int(eval(rowInfo))) for p in range(int(eval(columnInfo)))]
    # grid = [[0] * int(eval(rowInfo))] * int(eval(columnInfo))
    for rowIndex, rowArr in enumerate(pointArr):
        for columnIndex, item in enumerate(rowArr):
            grid[columnIndex][rowIndex] = eval(item)
    # Year data for the semilogy plot
    y = XArr

    # index data - taken at end of every
    # decade - for the semilogy plot

    # coding:utf-8
    plot.rcParams['axes.unicode_minus'] = False  # 用来正常显示负号

    # Display grid
    # plot.grid(True, which="both")

    # Linear X axis, Logarithmic Y axis

    # plot.semilogy(years, indexValues2)

    # plot.ylim([10, 21000])
    #
    # plot.xlim([1900, 2020])

    # Provide the title for the semilogy plot
    plot.title('多道图', fontproperties=myfont)

    # Give x axis label for the semilogy plot
    plot.xlabel('里程 米', fontproperties=myfont)

    # Give y axis label for the semilogy plot
    plot.ylabel('磁场 nT', fontproperties=myfont)

    plot.gca().xaxis.set_major_locator(ticker.MultipleLocator(100))

    red = Color("#1c54b2")
    colors = list(red.range_to(Color("#33bfff"), int(eval(columnInfo))))

    newColors = ["#007bb2", "#00b0ff", "#33bfff"]

    for index, layerArr in enumerate(grid):
        plot.semilogy(y, layerArr, color=newColors[0], linewidth=0.3)

    myfig.savefig(resultPath, dpi=300, format='png')  # save myfig
    #
    file_like = open(resultPath, mode="rb")
    return StreamingResponse(file_like, media_type="image/png")

if __name__ == '__main__':
    import uvicorn
    uvicorn.run(app=app,
                host="0.0.0.0",
                port=8003,
                workers=1)