<?php

namespace App\Controller;

use App\Entity\Temperature;
use Symfony\Bundle\FrameworkBundle\Controller\AbstractController;
use Symfony\Component\Routing\Annotation\Route;

class TemperatureController extends AbstractController
{
    /**
     * @Route("/temperature", name="temperature")
     */
    public function index()
    {
        $temps = $this->getDoctrine()
          ->getRepository(Temperature::class)
          ->findAll();
        
        // Triage seulement pour les valeurs ajoutées à la main pour démo
        usort($temps, array($this, "date_sort"));

        $timeString = [];

        foreach ($temps as $value) {
            $date = $value->getCreatedAt()->format('Y-m-d H:i:s');
            array_push($timeString, ['celsius' => $value->getCelsius(), "createdAt" => $date]);
        }

        return $this->render('temperature/index.html.twig', [
            'controller_name' => 'TemperatureController',
            'temps' => $temps,
            'tempString' => $timeString,
        ]);
    }

    function date_sort($a, $b) {
        $aTime = $a->getCreatedAt();
        $bTime = $b->getCreatedAt();
        if ($aTime==$bTime) return 0;
        return ($aTime<$bTime)?-1:1;
    }
}
