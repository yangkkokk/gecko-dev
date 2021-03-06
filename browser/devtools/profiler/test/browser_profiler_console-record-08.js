/* Any copyright is dedicated to the Public Domain.
   http://creativecommons.org/publicdomain/zero/1.0/ */

/**
 * Tests if the profiler can correctly handle sequential console recordings,
 * finished in reverse order, and the second call to `console.profileEnd`
 * contains the same label as the first call.
 */

let test = Task.async(function*() {
  let [target, debuggee, panel] = yield initFrontend(SIMPLE_URL);
  let { $, EVENTS, gFront, RecordingsListView, ProfileView } = panel.panelWin;

  yield consoleProfile(gFront, "1");
  yield consoleProfile(gFront, "2");

  let firstRecordingDisplayed = panel.panelWin.once(EVENTS.RECORDING_DISPLAYED);
  yield consoleProfileEnd(gFront, "1");
  yield firstRecordingDisplayed;
  ok(true, "The newly finished console recording was automatically displayed.");

  is(RecordingsListView.itemCount, 2,
    "There should be two recordings visible.");
  is(RecordingsListView.items[0], RecordingsListView.selectedItem,
    "The first recording item should be selected.");

  is(RecordingsListView.items[0].attachment.profilerData.profileLabel, "1",
    "The profile label for the first recording is correct.");
  ok(!RecordingsListView.items[0].isRecording,
    "The 'isRecording' flag for the first recording is correct.");

  is(RecordingsListView.items[1].attachment.profilerData.profileLabel, "2",
    "The profile label for the second recording is correct.");
  ok(RecordingsListView.items[1].isRecording,
    "The 'isRecording' flag for the second recording is correct.");

  gFront.once("profileEnd", () => {
    ok(false, "The second console recording shouldn't have ended.")
  });
  panel.panelWin.once(EVENTS.RECORDING_DISPLAYED, () => {
    ok(false, "The second console recording shouldn't have been displayed.");
  });

  console.profileEnd("1");
  yield DevToolsUtils.waitForTime(1000);

  yield teardown(panel);
  finish();
});

function* consoleProfile(front, label) {
  let notified = front.once("profile");
  console.profile(label);
  yield notified;
}

function* consoleProfileEnd(front, label) {
  let notified = front.once("profileEnd");
  console.profileEnd(label);
  yield notified;
}
