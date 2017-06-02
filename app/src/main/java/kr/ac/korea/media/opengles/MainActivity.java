package kr.ac.korea.media.opengles;

import android.content.Context;
import android.content.res.AssetManager;
import android.opengl.GLSurfaceView;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.MotionEvent;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {

        // call superclass method
        super.onCreate(savedInstanceState);

        // create and set OpenGL ES surface view
        setContentView(new MyGLSurfaceView(this));
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native void surfaceCreated(AssetManager assetManager);
    public native void surfaceChanged(int width, int height);
    public native void drawFrame(float deltaTime);
    public native void screenSize(int width, int height);
    public native void touchEvent(float x, float y, int motion);

    private class MyGLSurfaceView extends GLSurfaceView {

        public MyGLSurfaceView(Context context) {

            // call super class method
            super(context);

            // set OpenGL ES version
            setEGLContextClientVersion(2);

            // set renderer
            setRenderer(new MyGLSurfaceRenderer());
        }

        @Override
        protected void onSizeChanged(int w, int h, int oldw, int oldh) {

            // call super class method
            super.onSizeChanged(w, h, oldw, oldh);

            // set screen size to view size
            screenSize(w, h);
        }

        @Override
        public boolean onTouchEvent(MotionEvent event) {

            // call native method
            switch (event.getAction()) {
            case MotionEvent.ACTION_DOWN:
                touchEvent(event.getX(), event.getY(), 1);
                break;
            case MotionEvent.ACTION_MOVE:
                touchEvent(event.getX(), event.getY(), 2);
                break;
            default:
                touchEvent(event.getX(), event.getY(), 3);
                break;
            }

            // return true
            return true;
        }
    }

    private class MyGLSurfaceRenderer implements GLSurfaceView.Renderer {

        // last time attribute for calculating delta time
        private long lastTime = System.currentTimeMillis();

        @Override
        public void onSurfaceCreated(GL10 gl, EGLConfig config) {

            // call native method
            surfaceCreated(getAssets());
        }

        @Override
        public void onSurfaceChanged(GL10 gl, int width, int height) {

            // call native method
            surfaceChanged(width, height);
        }

        @Override
        public void onDrawFrame(GL10 gl) {

            // calculate delta time
            long currentTime = System.currentTimeMillis();
            float deltaTime = (float) (currentTime - lastTime) / 1000.0f;
            lastTime = currentTime;

            // call native method
            drawFrame(deltaTime);
        }
    }
}
