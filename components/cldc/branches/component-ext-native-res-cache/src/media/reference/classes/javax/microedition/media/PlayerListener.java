/*
 *   
 * 
 * Copyright  1990-2006 Sun Microsystems, Inc. All Rights Reserved.
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License version
 * 2 only, as published by the Free Software Foundation. 
 * 
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License version 2 for more details (a copy is
 * included at /legal/license.txt). 
 * 
 * You should have received a copy of the GNU General Public License
 * version 2 along with this work; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 * 02110-1301 USA 
 * 
 * Please contact Sun Microsystems, Inc., 4150 Network Circle, Santa
 * Clara, CA 95054 or visit www.sun.com if you need additional
 * information or have any questions. 
 */

package javax.microedition.media;

/**
 * <CODE>PlayerListener</CODE> is the interface for receiving 
 * asynchronous
 * events generated by <code>Players</code>.  Applications may implement
 * this interface and register their implementations with
 * the <code>addPlayerListener</code> method in <code>Player</code>.
 * <p>
 * A number of standard <code>Player</code> events are defined
 * here in this interface.  Event types are defined as strings
 * to support extensibility as different implementations
 * may introduce proprietary events by adding new event types.
 * To avoid name conflicts, proprietary events should be named
 * with the "reverse-domainname" convention.  For example, a
 * company named "mycompany" should name its proprietary event
 * names with strings like <code>"com.mycompany.myEvent"</code> etc.
 * <p>
 * Applications that rely on proprietary events may
 * not function properly across different implementations.
 * In order to make the applications that use those events to behave
 * well in environments that don't implement them,
 * <code>String.equals()</code> should
 * be used to check the event.
 * <P> 
 * <h4>Code fragment for catching standard events in playerUpdate()</h4>
 * <blockquote>
 * <code>
 *  if (eventType == PlayerListener.STARTED) {...}
 * </code>
 * </blockquote>
 * <h4>Code fragment for catching proprietary events in playerUpdate()</h4>
 * <blockquote>
 * <code>
 *  if (eventType.equals("com.company.myEvent")) {...}
 * </code>
 * </blockquote>
 *
 * @see Player
 * 
 */
public interface PlayerListener {

    /**
     * Posted when a <code>Player</code> is started.
     * When this event is received, the <code>eventData</code> parameter
     * will be a <code>Long</code> object designating the media
     * time when the <code>Player</code> is started.
     * <p>
     * Value <code>started</code> is assigned to <code>STARTED</code>.
     */
    String STARTED = "started";

    /**
     * Posted when a <code>Player</code> stops in response to the
     * <code>stop</code> method call.
     * When this event is received, the <code>eventData</code> parameter
     * will be a <code>Long</code> object designating the media 
     * time when the <code>Player</code> stopped.
     * <p>
     * Value <code>stopped</code> is assigned to <code>STOPPED</code>.
     */
    String STOPPED = "stopped";


    /**
     * Posted when a <code>Player</code> is stopped as responding to
     * the <code>setStopTime</code> call using the 
     * <code>StopTimeControl</code>.
     * When this event is received, the <code>eventData</code> parameter
     * will be a <code>Long</code> object designating the media 
     * time when the <code>Player</code> is stopped.
     * <p>
     * Value <code>stoppedAtTime</code> is assigned to 
     * <code>STOPPED_AT_TIME</code>.
     */
    String STOPPED_AT_TIME = "stoppedAtTime";


    /**
     * Posted when a <code>Player</code> has reached the
     * end of the media.
     * When this event is received, the <code>eventData</code> parameter
     * will be a <code>Long</code> object designating the media 
     * time when the <code>Player</code> reached end of media and stopped.
     * <p>
     * Value <code>endOfMedia</code> is assigned to 
     * <code>END_OF_MEDIA</code>.
     */
    String END_OF_MEDIA = "endOfMedia";

    /**
     * Posted when the duration of a <code>Player</code> is updated.
     * This happens for some media types where the duration cannot
     * be derived ahead of time.  It can only be derived after the
     * media is played for a period of time -- for example, when it 
     * reaches a key frame with duration info; or when it reaches 
     * the end of media.
     * <p>
     * When this event is received, the <code>eventData</code> parameter
     * will be a <code>Long</code> object designating the duration 
     * of the media.
     * <p>
     * Value <code>durationUpdated</code> is assigned to 
     * <code>DURATION_UPDATED</code>.
     */
    String DURATION_UPDATED = "durationUpdated";

    /**
     * Posted when the system or another higher priority
     * application has temporarily taken control of an
     * exclusive device which was 
     * previously available to the <code>Player</code>.  
     * <p>
     * The <code>Player</code> will be in the <i>REALIZED</i> 
     * state when this event is received.
     * <p>
     * This event must
     * be followed by either a <code>DEVICE_AVAILABLE</code>
     * event when the device becomes available again,
     * or an <code>ERROR</code> event if the device
     * becomes permanently unavailable.
     * <p>
     * The <code>eventData</code> parameter is a <code>String</code>
     * specifying the name of the device.
     * <p>
     * Value <code>deviceUnavailable</code> is assigned to 
     * <code>DEVICE_UNAVAILABLE</code>.
     */
    String DEVICE_UNAVAILABLE = "deviceUnavailable";

    /**
     * Posted when the system or another higher priority
     * application has released an exclusive device 
     * which is now available to the <code>Player</code>.
     * <p>
     * The <code>Player</code> will be in the <i>REALIZED</i> 
     * state when this event is received.  The application
     * may acquire the device with the 
     * <code>prefetch</code> or <code>start</code> method.
     * <p>
     * A <code>DEVICE_UNAVAILABLE</code> event must
     * preceed this event.
     * <p>
     * The <code>eventData</code> parameter is a <code>String</code>
     * specifying the name of the device.
     * <p>
     * Value <code>deviceAvailable</code> is assigned to 
     * <code>DEVICE_AVAILABLE</code>.
     */
    String DEVICE_AVAILABLE = "deviceAvailable";

    /**
     * Posted when the volume of an audio device is changed.
     * When this event is received, the <code>eventData</code> parameter
     * will be a <a href="control/VolumeControl.html">
     * <code>VolumeControl</code></a>
     * object.  The new volume
     * can be queried from the <code>VolumeControl</code>.
     * <p>
     * Value <code>volumeChanged</code> is assigned to 
     * <code>VOLUME_CHANGED</code>.
     */
    String VOLUME_CHANGED = "volumeChanged";


    /**
     * Posted when the size of the video is changed either because
     * the source video size or the display size is changed.  
     * When this event is received, the <code>eventData</code> parameter
     * will be a <a href="control/VideoControl.html">
     * <code>VideoControl</code></a>
     * object.  The new sizes
     * can be queried from the <code>VideoControl</code>.
     * <p>
     * Value <code>sizeChanged</code> is assigned to 
     * <code>SIZE_CHANGED</code>.
     */
    String SIZE_CHANGED = "sizeChanged";


    /**
     * Posted when an error had occurred.
     * When this event is received, the <code>eventData</code> parameter
     * will be a <code>String</code> object specifying the error message.
     * <p>
     * Value <code>error</code> is assigned to <code>ERROR</code>.
     */
    String ERROR = "error";

    /**
     * Posted when a <code>Player</code> is closed.
     * When this event is received, the <code>eventData</code> parameter
     * is null.
     * <p>
     * Value <code>closed</code> is assigned to <code>CLOSED</code>.
     */
    String CLOSED = "closed";


    /**
     * Posted when recording is started.
     * <p>
     * When this event is received, the <code>eventData</code> parameter
     * will be a <code>Long</code> object designating the media
     * time when the recording is started.
     * <p>
     * Value <code>recordStarted</code> is assigned to 
     * <code>RECORD_STARTED</code>.
     */
    String RECORD_STARTED = "recordStarted";

    /**
     * Posted when recording is stopped.
     * <p>
     * When this event is received, the <code>eventData</code> parameter
     * will be a <code>Long</code> object designating the media 
     * time when the recording stopped.
     * <p>
     * Value <code>recordStopped</code> is assigned to 
     * <code>RECORD_STOPPED</code>.
     */
    String RECORD_STOPPED = "recordStopped";

    /**
     * Posted when an error occurs during the recording.
     * The current recording will be discarded.  The 
     * application may set a new record location or
     * stream to start recording again.
     * When this event is received, the <code>eventData</code> parameter
     * will be a <code>String</code> object specifying the error message.
     * <p>
     * Value <code>recordError</code> is assigned to
     * <code>RECORD_ERROR</code>.
     */
    String RECORD_ERROR = "recordError";

    /**
     * Posted when the <code>Player</code> enters into a buffering mode.
     * Applications may require this event to handle other tasks.
     * <p>
     * When this event is received, the <code>eventData</code> parameter
     * will be a <code>Long</code> object designating the media
     * time when the buffering is started.
     * <p>
     * Value <code>bufferingStarted</code> is assigned to 
     * <code>BUFFERING_STARTED</code>.
     */
    String BUFFERING_STARTED = "bufferingStarted";

    /**
     * Posted when the <code>Player</code> leaves the buffering mode.
     * Applications may require this event to handle other tasks.
     * <p>
     * When this event is received, the <code>eventData</code> parameter
     * will be a <code>Long</code> object designating the media 
     * time when the buffering stopped.
     * <p>
     * Value <code>bufferingStopped</code> is assigned to 
     * <code>BUFFERING_STOPPED</code>.
     */
    String BUFFERING_STOPPED = "bufferingStopped";


    /**
     * This method is called to deliver an event to a registered
     * listener when a <code>Player</code> event is observed.
     *
     * @param player The player which generated the event.
     * @param event The event generated as defined by the enumerated types.
     * @param eventData The associated event data.
     */
    void playerUpdate(Player player, String event, Object eventData);
}


