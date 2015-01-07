<?php
  global $base_url;

  // change login text if on the catalog site
  if (strpos($base_url,'catalog') !== FALSE) {

    if (!user_is_logged_in()) {
      $link_text = 'Sign in';
      $link_path = $base_url . '/user/login';
    }
    else {
      $link_text = 'Sign out';
      $link_path = $base_url . '/user/logout';
    }

  }
  else {

    if (!user_is_logged_in()) {
      $link_text = 'Log in';
      $link_path = $base_url . '/user/login';
    }
    else {
      $link_text = 'Log out';
      $link_path = $base_url . '/user/logout';
    }

  }

?>
    <h3>Contact Info</h3>
    <p><?php print $contact['address']; ?></p>
    <p>
      <a href="http://oregonstate.edu/copyright">Copyright</a> &copy; <?php print date("Y"); ?><br />
      <?php if (!empty($contact['webmaster'])): ?>
        <a href="<?php print $contact['webmaster']; ?>">Webmaster</a><br />
      <?php endif; ?>
      <a href="http://oregonstate.edu/disclaimer">Disclaimer</a><br />
      <a href="<?php print $link_path; ?>"><?php print $link_text; ?></a>
    </p>
