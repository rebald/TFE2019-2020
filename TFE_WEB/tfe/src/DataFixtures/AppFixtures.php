<?php

namespace App\DataFixtures;

use App\Entity\User;
use Doctrine\Bundle\FixturesBundle\Fixture;
use Doctrine\Persistence\ObjectManager;
use Symfony\Component\Security\Core\Encoder\UserPasswordEncoderInterface;

class AppFixtures extends Fixture
{
    private $encoder;

    public function __construct(UserPasswordEncoderInterface $encoder)
    {
        $this->encoder = $encoder;
    }

    public function load(ObjectManager $manager)
    {
        $user = new User();

        $user->setEmail('nathan@gmail.com');
        $password = $this->encoder->encodePassword($user, 'nathan');
        $user->setPassword($password);
        $user->setRoles(['ROLE_ADMIN', 'ROLE_USER']);

        $user2 = new User();

        $user2->setEmail('nathan2@gmail.com');
        $password = $this->encoder->encodePassword($user2, 'nathan');
        $user2->setPassword($password);
        $user2->setRoles(['ROLE_USER']);

        $manager->persist($user);
        $manager->persist($user2);
        $manager->flush();
    }
}
