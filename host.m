s = serialport('COM9',115200,'DataBits',8,'StopBits',1);
s.InputBufferSize = 1000000;

pre_data_length = 8;
reduce_resolution_rate = 2;
COL = 188/reduce_resolution_rate + 2;
ROW = 120/reduce_resolution_rate;
zoom = 1;

while true
    no_sof = 1;
    detector = read(s,1,"uint8");
    if detector == 204
        detector = read(s,1,"uint8");
        if detector == 208
            detector = read(s,1,"uint8");
            if detector == 216
                no_sof = 0;
                stop_usb = read(s,1,"uint8");
                if stop_usb == 1 % 停止运行
                    delete(s);
                    return
                end
                x = read(s,1,"uint8"); % 解包
                y = read(s,1,"uint8");
                r = read(s,1,"uint8");
                fps = read(s,1,"uint8");
                blank = read(s,COL-pre_data_length,"uint8");
                raw_data = read(s,COL*ROW,"uint8");
            end
        end
    end

    if no_sof == 0
        mat = reshape(raw_data,[COL,ROW]); % 图片部分
        I = imresize(transpose(mat)/256,zoom*reduce_resolution_rate);
        imshow(I);
        text(170*zoom,5*zoom,['fps=',num2str(fps)],'Color',[1,1,1]);
        viscircles([x*zoom,y*zoom], r*zoom,'Color','green');
        text(10*zoom,10*zoom,['x=',num2str(x)],'Color',[1,1,1]);
        text(10*zoom,15*zoom,['y=',num2str(y)],'Color',[1,1,1]);
        text(10*zoom,20*zoom,['r=',num2str(r)],'Color',[1,1,1]);
    end
    flush(s); % 清空缓存
end