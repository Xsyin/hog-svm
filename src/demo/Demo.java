package demo;


public class Demo {
	static{
		System.loadLibrary("SvmDetect");
	}
	
	
	private native double[] get_hoop_position(int frameCount, String path, String model);
	
	public static void main(String[] args){
		int frameCount = 10;
		String video_path = "/home/xsyin/video/01.mp4";
		String model = "wsv.dat";
		
		Demo detector = new Demo();
		
		double[] rects = {};
		
		//rects = {state, x, y, width, height}
		//  state:1           表示模型数据文件错误
	    //  2           表示视频文件载入错误
	    //  4           表示没有检测到
	    //  8           表示检测到了但是效果不好
	    //  24 =16+8    表示检测到了，而且效果不错
		rects = detector.get_hoop_position(frameCount, video_path, model);
		if(rects[0] == 1.0){
			System.out.println("model file failed!");
		}else if(rects[0] == 2.0){
			System.out.println("read video failed!");
		}else if(rects[0] == 4.0){
			System.out.println("detect nothing");
		}
		else{
			for(int i=1; i<rects.length; i++){
				System.out.println(rects[i]);
			}
		}
		
		
	}
}
